# ParallelProgramming-RaniaDervisevic

-made it so the loop bounderis correctly iterate over the array without exceeding bounds. 
-the original code alocated memory but never released it, so I added 'free(iarray)' to ensure everything is freed. 
-variables initialised properly at the beginning to prevent undefined behavior.



gcc -Wall -Wextra -g -std=c99 -o memory_demo main.c
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./memory_demo
==9238== Memcheck, a memory error detector
==9238== Copyright (C) 2002-2024, and GNU GPL'd, by Julian Seward et al.
==9238== Using Valgrind-3.24.0 and LibVEX; rerun with -h for copyright info
==9238== Command: ./memory_demo
==9238== 
==9238== 
==9238== HEAP SUMMARY:
==9238==     in use at exit: 0 bytes in 0 blocks
==9238==   total heap usage: 1 allocs, 1 frees, 40 bytes allocated
==9238== 
==9238== All heap blocks were freed -- no leaks are possible
==9238== 
==9238== For lists of detected and suppressed errors, rerun with: -s
==9238== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
