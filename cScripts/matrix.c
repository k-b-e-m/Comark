#include <time.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <linux/perf_event.h>

#ifdef __ARM_NEON

#include <arm_neon.h>			// NEON intrinsics

#else

#include <immintrin.h>			// AVX intrinsics

#endif

#include <assert.h>

/* Vector size, must be a multiple of 16. */
#define N	128

typedef unsigned long long ull_t;

struct timespec tic, toc;

/* Measures a timestamp in nanosecond precision. */
void bench_measure(struct timespec *time) {
	clock_gettime(CLOCK_REALTIME, time);
}

/* Computes the time in nanoseconds since the last measurement. */
ull_t bench_compute(struct timespec *toc, struct timespec *tic) {
	ull_t result = (toc->tv_sec - tic->tv_sec) * (ull_t) 1000000000;
	result += (toc->tv_nsec - tic->tv_nsec);
	return result;
}

/* Print times in miliseconds after converting from nanoseconds. */
void bench_print(char *str, ull_t * v, int size) {
	printf("%s (in microsec): ", str);
	for (int i = 0; i < size; i++) {
		printf("%llu ", v[i] / 1000);
	}
	printf("\n");
}

int check_add(float *ans) {
	/* Compare a vector with the right answer. */
	for (int i = 0; i < N * N; i++) {
		if (fabsf(ans[i] - 3.0f) > 1e-5) {
			return 0;
		}
	}
	return 1;
}

int check_mul(float *kat, float *ans) {
	/* Compare two matrices. */
	for (int i = 0; i < N * N; i++) {
		if (fabsf(ans[i] - kat[i]) > 1e-5) {
			return 0;
		}
	}
	return 1;
}

/* Implement matrix addition in C, and disable automatic vectorization. */
__attribute__((optimize("no-tree-vectorize")))
ull_t matrix_add_c(float *a, float *b) {
	float ans[N * N];

	bench_measure(&tic);
	for (int i = 0; i < N * N; i++) {
		ans[i] = a[i] + b[i];
	}
	bench_measure(&toc);
	assert(check_add(ans));
	return bench_compute(&toc, &tic);
}

/* Implement matrix addition using vector instructions on Intel or ARM. */
ull_t matrix_add_vector(float *a, float *b) {
	float ans[N * N];
	ull_t result;

	/* For each of the functions below, measure the time and return it. */
	bench_measure(&tic);
#if __ARM_NEON
	for (int i = 0; i < N * N; i += 4) {
		float32x4_t ax = vld1q_f32(a + i);
		float32x4_t bx = vld1q_f32(b + i);
		float32x4_t cx = vaddq_f32(ax, bx);
		vst1q_f32(ans + i, cx);
	}
#else
	for (int i = 0; i < N * N; i += 8) {
		__m256 ax = _mm256_loadu_ps((const float *)(a + i));
		__m256 bx = _mm256_loadu_ps((const float *)(b + i));
		__m256 cx = _mm256_add_ps(ax, bx);
		_mm256_storeu_ps((float *)(ans + i), cx);
	}
#endif
	bench_measure(&toc);
	assert(check_add(ans));
	return bench_compute(&toc, &tic);
}

ull_t matrix_multiply(float *C, const float *A, const float *B) {
	ull_t result;

	bench_measure(&tic);
	// For each row...
	for (size_t row = 0; row < N; row++) {
		// For each col...
		for (size_t col = 0; col < N; col++) {
			C[row * N + col] = 0;
			// For each element in the row/col pair...
			for (size_t idx = 0; idx < N; idx++) {
				// Accumulate the partial results
				C[row * N + col] += A[row * N + idx] * B[idx * N + col];
			}
		}
	}
	bench_measure(&toc);
	return bench_compute(&toc, &tic);
}

ull_t matrix_multiply_blocked(float *C, const float *A, const float *B) {
	ull_t result;

	bench_measure(&tic);
	memset(C, 0, N * N * sizeof(float));
	// For each row...
	for (size_t row = 0; row < N; row++) {
		// For each block in the row...
		// Solve for 16 elements at a time
		for (size_t block = 0; block < N; block += 16) {
			// For each chunk of A/B for this block
			for (size_t chunk = 0; chunk < N; chunk += 16) {
				// For each row in the chunk
				for (size_t sub_chunk = 0; sub_chunk < 16; sub_chunk++) {
					// Go through all the elements in the sub chunk
					for (size_t idx = 0; idx < 16; idx++) {
						C[row * N + block + idx] +=
							A[row * N + chunk + sub_chunk] *
							B[chunk * N + sub_chunk * N + block + idx];
					}
				}
			}
		}
	}
	bench_measure(&toc);
	return bench_compute(&toc, &tic);
}

ull_t matrix_multiply_blocked_column(float *C, const float *A, const float *B) {
	ull_t result;

	bench_measure(&tic);
	memset(C, 0, N * N * sizeof(float));
	// For each chunk of columns
	for (size_t col_chunk = 0; col_chunk < N; col_chunk += 16) {
		// For each row in that chunk of columns...
		for (size_t row = 0; row < N; row++) {
			// For each block of elements in this row of this column chunk
			// Solve for 16 elements at a time
			for (size_t tile = 0; tile < N; tile += 16) {
				// For each row in the tile
				for (size_t tile_row = 0; tile_row < 16; tile_row++) {
					// Solve for each element in this tile row
					for (size_t idx = 0; idx < 16; idx++) {
						C[row * N + col_chunk + idx] +=
							A[row * N + tile + tile_row] *
							B[tile * N + tile_row * N + col_chunk + idx];
					}
				}
			}
		}
	}
	bench_measure(&toc);
	return bench_compute(&toc, &tic);
}

int main(int argc, char *argv[]) {
	float a[N * N], b[N * N], x[N * N], y[N * N], z[N * N], w[N * N];
	ull_t results[3];

	/* Initialize with constants for it to be easy to check result. */
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			a[i * N + j] = 1.0f;
			b[i * N + j] = 2.0f;
			x[i * N + j] = 1.5f;
			y[i * N + j] = 2.1f;
			z[i * N + j] = 0.0f;
			w[i * N + j] = 0.0f;
		}
	}

	/* Run vector addition benchmarks. */
	results[0] = results[1] = 0;
	for (int i = 0; i < 1000; i++) {
		results[0] += (matrix_add_c(a, b));
		results[1] += (matrix_add_vector(a, b));
	}
	/* Print timings for standard and vectorized. */
	bench_print("matrix add", results, 2);

	/* Run matrix multiplication benchmarks. */
	results[0] = results[1] = results[2] = 0;
	for (int i = 0; i < 1000; i++) {
		results[0] += (matrix_multiply(z, x, y));
		results[1] += (matrix_multiply_blocked(w, x, y));
		assert(check_mul(z, w));
		results[2] += (matrix_multiply_blocked_column(w, x, y));
		assert(check_mul(z, w));
	}
	/* Print timings for standard, blocked and blocked per column. */
	bench_print("matrix mul", results, 3);
	return 0;
}
