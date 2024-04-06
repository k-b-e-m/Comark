# Parallelism
## Characterizations of Parallelism
### Microscopic vs macroscopic
![[microscopic parralelism.png]]
More specific, microscopic refers to parallelism within a component for example a processor. macroscopic parallelism is within a larger system.
### Symmetric vs asymmetric
*Symmetric* is used to characterize a design that uses replications of identical elements. For example having 4 identical processors is symmetric, but if each of them is a different kind of processor, it is called *Asymetric.*
### Fine-grain vs coarse-grain
*fine-grain* is parallelism on the individual instructions and data element, *coarse-grain* is parallelism between programs and large level data.
### Explicit vs implicit
*Implicit parralelism* is when the parralelism is handled automatic wheras *explicit parralelism* is where the programmer must control each parallel unit.
## Types of parallel Architectures
**Flynn classification:**
![[Flynn classification.png]]
### Single Instruction Single Data (SISD)
This architecture does not support macroscoping parralelism.
Often called "sequential architecture" or "uniprocessor".
### Single Instruction Multiple Data (SIMD)
This specifies a system where each instruction specifies a single operation. However this instruction can affect multiple data items at the same time.
### Multiple Instructions Multiple Data
Each processor performs independent computations at the same time.

