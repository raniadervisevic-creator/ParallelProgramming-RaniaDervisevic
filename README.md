# Lab 07 - OpenMP Stencil Optimization

The goal of this task was to see how different OpenMP parallelization strategies affect the speed and cache behavior of a 2D 5-point stencil calculation. I compiled and ran three versions of the code (`stencil_opt2`, `stencil_opt4`, and `stencil_opt6`) and compared their timings.

We found out that repeatedly starting and stopping parallel regions on every iteration slows down the program because of thread synchronization overhead. When the parallel region was moved outside the main loop in `stencil_opt4`, the total time dropped by about 26 seconds (`258.79 s` down to `232.89 s`). Manually splitting the grid rows per thread in `stencil_opt6` gave the fastest stencil computation time (`153.33 s`) because each thread kept working on the same part of memory across all iterations, though the overall runtime was still limited by memory speed due to the cache flush running every iteration.

## Questions

**How many threads your CPU used to execute the code?**
My CPU used 4 threads to execute all three implementations, which is printed at the beginning of each run using `omp_get_num_threads()`.

**What are the parts of the code that were improved? What strategies were used to improve the code?**
The main parts that were improved are how the parallel regions are set up, how threads synchronize between loops, and how the grid rows are split across threads. `stencil_opt2` puts a separate `#pragma omp parallel for` on each loop (init, flush, and stencil), which creates a lot of overhead because threads keep starting and stopping every iteration. `stencil_opt4` fixes this by putting one `#pragma omp parallel` block outside the 10,000 iteration loop so the 4 threads stay alive the whole time. It also adds `nowait` to the init and flush loops so threads don't stop and wait when they don't need to, and uses `#pragma omp single` so only one thread swaps the `x` and `xnew` pointers and prints progress. `stencil_opt6` removes `#pragma omp for` completely and splits the grid manually inside one parallel region—each thread calculates its own row range (`jltb` to `jutb`) at the start, initializes and flushes its own part, and keeps working on the exact same memory slice across all iterations.

**What is the difference between explicit and implicit barriers inside the code and did they exist inside any of these examples? What do they actually mean?**
A barrier is a point where all threads have to pause and wait for every other thread to catch up before moving on, so nobody reads old values or swaps pointers too early. Implicit barriers are added automatically by OpenMP at the end of blocks like `#pragma omp parallel`, `#pragma omp for`, and `#pragma omp single`, while explicit barriers are written manually in the code using `#pragma omp barrier`.

Both kinds show up in these examples. `stencil_opt2` only has implicit barriers at the end of every `#pragma omp parallel for` loop. `stencil_opt4` uses implicit barriers after the stencil `#pragma omp for` and `#pragma omp single` blocks (so threads finish updating `xnew` before `SWAP_PTR` runs and wait for the swap before starting the next step), while skipping the implicit barriers on init and flush with `nowait`. `stencil_opt6` uses explicit `#pragma omp barrier` lines right before and after `SWAP_PTR` so threads sync their neighbor border rows before the next iteration, plus an implicit barrier at the end of the outer `#pragma omp parallel` block.

 - Terminal Results:(terminal_results.png)

