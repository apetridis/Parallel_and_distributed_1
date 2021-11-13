/*********************************************************************
 * File: mycilk.c
 * 
 * Author: Alexandros Petridis
 * Date: September 2021
 *
 * Description: Implementations of header file mycilk.h
 ********************************************************************/

#include "mycilk.h"

double cilk_implementation(
    uint32_t       * const row,
    uint32_t       * const col,
    uint32_t const         N,
    uint32_t const         nz
) {
    struct timespec start_time;
    struct timespec end_time;    

    int *C = (int *) malloc(nz * sizeof(int));  /* C = A.*(A*A) where A matrix from .mtx file */
    for (int i=0; i<N; i++)
        C[i] = 0;
    
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    cilk_for (int i=0; i<N; i++)    /* only for loop that can run in parallel for result to be correct */
        for (int j=col[i]; j<col[i+1]; j++)
            for (int k=col[row[j]]; k<col[row[j]+1]; k++)
                if (mybinarySearch((int *)row, j+1, col[i+1]-1, row[k]) != -1)
                    C[i]++;
                
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double time_needed;
    time_needed = (end_time.tv_sec - start_time.tv_sec) * 1e9;
    time_needed = (time_needed + (end_time.tv_nsec - start_time.tv_nsec)) * 1e-9;

    return time_needed;
}