#include <stdio.h>
#include <stdlib.h>

// Define 3 global variables just for testing purposes.
long g1;
long g2;

long result;

/* Usage of extended assembler (for our purposes). The general syntax is something like this:
 * asm volatile ("assembly instructions go here": output : input : scratch registers and other information);
 *
 * Now let us look at the parts:
 * "assembly instruction": 
 *      This often looks like this: "<instruction 1>\n\t <instruction 2>\nt\t ..."
 *
 * output: the C variables the assembly instructions would like to write to.
 *
 * input: the C variables the assembly instructions would like to read.
 *
 * You can request that the value of the variable be placed in a register or memory location
 *
 * The best way to learn is via examples. Once you understand the syntax, it is very simple! */

void task1() {
    // Task 1: Do g1=1 with assembly
    //
    // So we want to do an instruction: movq $1, <memory location of g1>. 
    // To do that, we can simply write:
    asm volatile ("movq $1, %[g] \n\t": [g] "=m" (g1)::);  // Explanation below

    // Let us print to test:
    printf("g1 is %ld\n", g1); // produces: g1 is 1

    // Let us break this down:
    //              asm volatile ("movq $1, %[g]\n\t": [g] "=m" (g1) :   :    );
    //                             -----------------   ------------          
    //                               ^                  ^              ^    ^      
    //                               |                  |              |    |      
    //  assembly instruction ---------                  |              |    | 
    //      by convention, we finish every instruction  |              |    |      
    //      with \n\t, i.e., newline and then tab.      |              |    | 
    //  Output ------------------------------------------              |    | 
    //      declares variable g1 as the output of the extended asm     |    | 
    //      "m" means that we want to access g1 as a memory location   |    | 
    //      "=" declares that g1 is only being written (not read)      |    | 
    //      the brackets [] assign an alias to the variable.           |    | 
    //      So in our assembly %[g] is going to represent              |    | 
    //      the global variable g1.                                    |    | 
    //                                                                 |    | 
    //  Input ----------------------------------------------------------    |
    //      We have no input here.                                          |
    //  Other info ----------------------------------------------------------
    //      No other info is necessary here
    //
    // The compiler produces the code: movq   $0x1,0x2ebc(%rip)
    // which moves value "1" into a memory location that represents g1.
}

void task2() {
    // Task 2: Do g2=2 but via a register 
    asm volatile ("movq $2, %[g]\n\t": [g] "=r" (g2)::);

    // Let us print to test:
    printf("g2 is %ld\n", g2); // produces: g2 is 2

    // Let us break down this one too:
    //              asm volatile ("movq $2, %[g]\n\t": [g] "=r" (g2):   :    );
    //                             -----------------   ------------          
    //                               ^                  ^            ^    ^      
    //                               |                  |            |    |      
    //  assembly instruction ---------                  |            |    | 
    //                                                  |            |    |      
    //                                                  |            |    | 
    //  Output ------------------------------------------            |    | 
    //      declares variable g2 as the output of this.              |    | 
    //      "r" declares that it should be placed in a register      |    | 
    //      "=" declares that it is only being written               |    | 
    //      the brackets assign an alias to the variable.            |    | 
    //      So in our assembly %[g] is going to represent            |    | 
    //      the global variable g1, but as a register                |    | 
    //                                                               |    | 
    //  Input --------------------------------------------------------    |
    //      We have no input here.                                        |
    //  Other info --------------------------------------------------------
    //      No other info is necessary here
    //
    //  Consequence:
    // The compiler replaces %[g] by some register and then at the end, writes the
    // value of that register to the g2 variable:
    //            mov    $0x2,%rax
    //            mov    %rax,0x2e93(%rip)        # 4018 <g2>
    //
    // Note the difference between Task 1 and 2. 
    // In Task 1, the compiler produced an assembly instruction of type:
    //      movq <immediate value>, <memory location>
    //
    // In Task 2, the compiler produced an assembly instruction of type:
    //      movq <immediate value>, <register>
    //
    // Both are valid, since an intel 86-64 machine supports both types of 
    // mov instructions. Otherwise, the compiler would have complained. 
    //
    // Not every combination register/memory location/immediate values
    // is valid with every instruction. So depending on the type of instruction we are
    // using, we need to pick the correct representation of a variable.
}


void task3() {
    // Task 3: do, g1=10; g2=20;
    asm volatile ("movq $10,%[g1]\n\t movq $20,%[g2]\n\t": [g1] "=r" (g1), [g2] "=r" (g2)::);
    //                                                     -----------------------------
    // Mostly the same.                                                   ^
    //                                                                    |  
    // Output ------------------------------------------------------------
    //      We can separate two output variables with comma. The rest is the same.
    printf("g1 is %ld, g2 is %ld\n",g1,g2); // produces: g1 is 10, g2 is 20

    // In C, we can break a long line into multiple lines with \
    // So we can write above asm as follows for clarity:
    
    asm volatile ("movq $10,%[g1]\n\t movq $20,%[g2]\n\t": \
                    [g1] "=r" (g1), [g2] "=r" (g2)::);

    // Or to make it even style it up more.
    //
    asm volatile (" movq $10,%[g1]                              \n\t   \
                    movq $20,%[g2]                              \n\t"  \
                    :[g1] "=r" (g1), [g2] "=r" (g2)   /*output*/       \
                    ::);
}

void task4() {
    // Task 4: Increment g1 
    asm volatile ("incq %[g]\n\t": [g] "=m" (g1):  :   "cc");
    // Here, we are incrementing g1 as a memory         ^
    // location. This is same as before.                |
    //                                                  |
    // Other info: --------------------------------------
    //      "cc" means this code is changing the flags (carry, overflow or so on)
    //      The compiler has no idea what we are doing with the assembly
    //      instructions. So if we are changing something about the registers, flags,
    //      etc. we have to tell the compiler. 
    //
    // Produces:
    //      incq   0x2e01(%rip)        # 4028 <g1>
    //
    printf("g1 is %ld\n", g1); // produces: g1 is 11


    // Now let's change g1 as a register. 
    // Here, g1 has to be both input and the output, because g1 
    // needs to be read into a register first. 
    // To increment g1, the compiler must first set up the proper code to read the value of
    // g1. Then it will need to produce some code to write the value of g1.
    // So we use + instead of = so signify that g1 is both read and written
    asm volatile ("incq %[g]\n\t": [g] "+r" (g1):  :   "cc");
    //                             -------------         ^   
    //                                  ^                |       
    //                                  |                |               
    // Output --------------------------                 |       
    //      + shows g1 is both an input and an output.   |        
    //      r says we want it to be in a register.       |      
    //      So the compiler loads up some register with  |    
    //      the value of g1, then increments the         |     
    //      register, then and writes its value back     |  
    //      to g1.                                       |  
    // Other info: ---------------------------------------
    //      "cc" means this code is changing the flags (carry, overflow or so on)
    //
    //  Produces the code:
    //
    //       mov    0x2e01(%rip),%rdx        # 4028 <g1>  # mov g1 to rdx
    //       inc    %rdx
    //       mov    %rdx,0x2df7(%rip)        # 4028 <g1>  # write rdx back to g1
    //
    printf("g1 is %ld\n",g1); // produces: g1 is 12
}

void task5() {
    // Task 5: Copy g1 to g2
    // Here, g1 is the input, and g2 is the output.
    asm volatile ("movq %[g1],%[g2]\n\t": [g2] "=mr" (g2):[g1] "r" (g1):);
    //                                    --------------  ------------
    //                                          ^            ^                    
    //                                          |            |                    
    // Output ----------------------------------             |
    //      g2 is the output. We don't care if it is         |           
    //      placed in a register or memory location.         |           
    //      So we say both m and r.                          |       
    //      It is only written so we have =                  |       
    //                                                       |   
    //  Input ------------------------------------------------
    //      We want g1 to be the input and in a register.
    //
    //  Note: There is no instruction in x86 assembly to move between
    //  memory locations (e.g., no mov (%rax),(%rbx) instruction).
    //  This means, we cannot use "m" with both g1 and g2. 
    //
    //  Produces:
    //      mov    0x2da9(%rip),%rax        # 4028 <g1>
    //      mov    %rax,0x2d9a(%rip)        # 4020 <g2>
    printf("g1 is %ld, g2 is %ld\n", g1, g2); // produces: g1 is 11, g2 is 11
}

// Task 6: Write a function to return the number of 1s in the binary
// representation of n. In C, you will need to write some kind of loop.
// In Intel assembly, we can do it with 1 instruction: popcnt.
// We can use it with a register and memory location oprands:
//      popcnt reg, memory location
//
long popcnt(long n) {
    long res;                                                                                                         
    asm("popcntq %[n],%[res]": [res] "=r"(res): [n] "r"(n): "cc");                                                    
    //                        ----------------- ----------   ^    
    //                               ^                  ^    |
    //                               |                  |    |
    //  Output -----------------------                  |    |                                   
    //      declares variable res as the output         |    | 
    //      and we want it to be a register.            |    | 
    //      We we are only writing it                   |    | 
    //                                                  |    | 
    //  Input -------------------------------------------    |
    //      n is the input and we want it loaded in a reg    |
    //  Other info -------------------------------------------
    //      We are changing the flags. 
    //
    //  Note: 
    //      By referring to the intel manuals, we can see that the
    //      target in this instruction (i.e., res), cannot be a memory
    //      location. So that's why we have to select "r" for res.
    //
    // The compiler produces the code: 
    //      popcnt %rdi,%rax
    //
    //  Because I compiled it with -O so the compiler was smart enough to figure
    //  out that there is no point in actually writing the value to the local
    //  variable res, because the return value of the function needs to be in 
    //  the register rax anyways!
   return res;                                                                                                       
}

void task6() {
    printf("# of 1s in 17 is %ld but # of 1s in 13 is %ld. Strange, no?\n", popcnt(17), popcnt(13));
}

void task7() {
    long *ptr;
    // First do, ptr = &g1 with assembly:
    // &gr in the input and ptr is the output so we write
    asm volatile ("movq %[g], %[ptr]\n\t"                                           \
            : [ptr] "=m" (ptr) /*output*/                                           \
            : [g] "r" (&g1)  /*input; the address of g1 must be loaded in a reg*/   \
            :);  

    printf("ptr points to %p and g1 is at %p\n", ptr, &g1);

    // Next, go g1=17 using ptr, i.e., do (*ptr) = 17;
    asm volatile ("movq $17, %[g]\n\t": [g] "=r" (*ptr)::);  
    // asm volatile ("movq $17, %[g]\n\t": [g] "=m" (*ptr)::);   // also works
    //
    // Basically, the same as above, just that now *ptr is the output. 
    printf("g1 is %ld\n", g1); // produces: g1 is 17
}

// The rest are optional.


void task8() {
    // Task 6: Compare g1 and g2. 
    //      If g1 > g2, then set result = 1.
    //      If g2 > g1, then set result = 2.
    //      If g1 == g2, then set result = 0;
    //
    //  Here, result will only be output. But g1 and g2 will be the input. 
    //  This is just an example to show that we can use labels normally,
    //  if we add the '%=' suffix to all the labels. The %= suffix will be
    //  replaced by a unique number every single time the compiler uses our
    //  block of code and thus it also plays nicely with various optimizations
    //  that the compiler can do.
    //
    //  We try this comparison in a for loop and compare g2 to g1, g1+1 and g1+2
    g1 = 10;
    g2 = 11;
    for (int i=0; i<3; i++) {
        asm volatile("                                                      \n\t\
                                cmpq %[g1],%[g2]                            \n\t\
                                jl task_6_g1_big%=      /*jump if g2<g1*/   \n\t\
                                je task_6_g1_g2_eq%=    /*jump if g2==g1*/  \n\t\
                                movq $2,%[result]        /*g2 is bigger*/   \n\t\
                                jmp task_6_end%=         /* goto end*/      \n\t\
              task_6_g1_big%=:  movq $1,%[result]                           \n\t\
                                jmp task_6_end%=                            \n\t\
              task_6_g1_g2_eq%=:                                            \n\t\
                                movq $0,%[result]                           \n\t\
              task_6_end%=:"    :  [result] "=rm" (result) /* output */     \
                                :  [g1] "r" (g1), [g2] "r" (g2) /* inputs*/ \
                                :  "cc");     /* we are changing the flags*/ 


        printf("g1=%ld, g2=%ld, and Result: %ld\n", g1, g2, result);
        g1++;  // increment g1
    }
}

void task9() {
    //  Task 9: Swap g1 and g2 by mov instructions only
    //  Here, we have to an extra scratch register. We need double % to use a register:
    printf("g1 is %ld, g2 is %ld\n",g1,g2); // produces: g1 is 13, g2 is 11
    asm volatile("                                                      \
            movq %[g1],%%rax                                        \n\t\
            movq %[g2],%[g1]                                        \n\t\
            movq %%rax,%[g2]                                        \n\t\
            ":[g1] "+r" (g1), [g2] "+r" (g2)::"rax");
    //                                          ^
    //                                          | 
    // Other info:------------------------------
    //  We notify the compiler that we are using the register rax
    //  as a scratch register. The compiler avoids using rax for g1 and g2
    //  as a result.
    printf("g1 is %ld, g2 is %ld\n", g1, g2); // produces: g1 is 11, g2 is 13
}

int main() {
    task1();
    task2();
    task3();
    task4();
    task5();
    task6();
    task7();
    task8();
    task9();
}
