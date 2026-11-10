# Lab 06 - Vectorization: FLOPs for Free

## Optimization Summary

- Iteration 0 (timestep.c): Baseline code without optimizations. Failed to vectorize due to control flow inside the loop (if statement) and floating-point math operation checks.
- Iteration 1 (timestep_opt1.c): Added #pragma omp simd reduction(min: mymindt). Auto-vectorization was still blocked by loop control flow and math traps.
- Iteration 2 (timestep_opt2.c): Added restrict keywords and private() clauses to eliminate pointer aliasing issues, but control flow still prevented full vectorization.
- Iteration 3 (timestep_opt3.c): Compiled using -fno-trapping-math and -fno-math-errno flags along with local loop scoping.

## Answers & Analysis

 Is it fully vectorized?
   - Iterations 0, 1, and 2 were not fully vectorized because GCC avoided vectorizing conditional statements containing division and sqrt() operations to prevent exception traps.
   - Iteration 3 was fully vectorized because -fno-trapping-math -fno-math-errno guaranteed floating-point operations would not throw traps, allowing GCC to generate SIMD vector masks.

 What vector length instructions were used?
   - The compiler generated 32-byte vectors (256-bit AVX instructions), processing 4 double-precision floats concurrently per vector lane.

 Which of the runs is the best?
   - Iteration 3 (timestep_opt3.c with math flags) achieved the best performance, full SIMD vectorization, and shortest runtime.# ParallelProgramming-RaniaDervisevic
