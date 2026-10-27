# Assignment 3: AoSoA Memory Layout and Performance Analysis

## Executive Summary
This project evaluates the performance characteristics of the **Array of Structures of Arrays (AoSoA)** memory layout versus traditional data structures like Array of Structures (AoS) and Structure of Arrays (SoA). By organizing contiguous vector elements of length $V$ within tiled structures, AoSoA aims to optimize spatial memory locality, maximize CPU cache line utilization, and enable efficient hardware SIMD autovectorization.

---

## Deliverables & Repository Structure
- `aosoa_measurement.cpp`: Core C++ benchmark application implementing the AoSoA kernel. Parametrized to run benchmarks over variable vector lengths ($V$) and dataset sizes ($N$).
- `Makefile`: Automated build script configured to systematically compile and execute benchmarks across all dataset combinations ($N = 1\text{K}, 10\text{K}, 1\text{M}, 10\text{M}$ and $V = 2, 4, 8, 16, 32, 64, 128, 256$).
- `graph.png`: Generated performance visualization plot.
- `README.md`: Comprehensive documentation, links, and detailed performance analysis.

---

## Google Spreadsheet & Performance Graph Links
- **Google Spreadsheet**: [View Benchmark Spreadsheet]https://docs.google.com/spreadsheets/d/1LqvG23c16tQvPSuse51GvLsU_YxleeGi4XhrnY2M1mY/edit?usp=sharing
- **Performance Graph**: [View Performance Graph](graph.png)

---

## Experimental Setup & Methodology
- **Vector Lengths ($V$) Tested**: $2, 4, 8, 16, 32, 64, 128, 256$
- **Dataset Sizes ($N$) Tested**: 
  - $1\text{K}$ ($1,000$ elements)
  - $10\text{K}$ ($10,000$ elements)
  - $1\text{M}$ ($1,000,000$ elements)
  - $10\text{M}$ ($10,000,000$ elements)
- **Compiler Options**: `g++ -O3 -Wall -std=c++17 -march=native`
- **Measurement Metric**: Execution time measured in milliseconds ($\text{ms}$).

---

## Comprehensive Performance Analysis

### 1. Small Scale Benchmarks ($N = 1\text{K}$ and $N = 10\text{K}$)
For smaller dataset sizes ($N = 1\text{K}$ and $N = 10\text{K}$), execution times are minimal ($< 1\text{ ms}$). 
- At these data scales, the entire memory footprint fits completely within the CPU's high-speed **L1 and L2 cache layers**.
- Memory latency bottlenecks are virtually non-existent, resulting in flat, uniform execution times regardless of the vector length ($V$) selected.

### 2. Large Scale Benchmarks ($N = 1\text{M}$ and $N = 10\text{M}$)
As the dataset size increases to $1\text{M}$ and $10\text{M}$ elements, data can no longer fit in cache, making memory bandwidth and cache line management the primary bottlenecks:
- **Cache Line Utilization**: Standard x86 CPU cache lines are 64 bytes wide. Packing contiguous $R, G, B$ color components in fixed block sizes of $V$ guarantees high spatial locality. Data fetched into cache lines is heavily consumed before eviction, minimizing cache misses.
- **Impact of Vector Length ($V$)**: 
  - **Small $V$ ($2, 4$)**: Show higher relative overhead due to increased structural loop boundary control overhead.
  - **Optimal $V$ ($16, 32, 64, 128$)**: Yield optimal performance by aligning closely with cache line sizes and SIMD vector register widths.
  - **Large $V$ ($256$)**: Demonstrates slight performance degradation or variance depending on register pressure and cache eviction policies.
- **SIMD Vectorization**: The fixed-width tiling in AoSoA allows compiler autovectorization (AVX2 / AVX-512) to execute vector instructions over contiguous sub-arrays without incurring the strided load/store penalties typical of standard AoS structures.
