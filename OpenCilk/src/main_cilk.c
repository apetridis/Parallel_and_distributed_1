/*********************************************************************
 * File: main_cilk.c
 * 
 * Author: Alexandros Petridis
 * Date: September 2021
 *
 * Description: Main file for OpenCilk 
 ********************************************************************/

#include "myhelpers.h"
#include "mycilk.h"


int main(int argc, char *argv[]) {

    int M, N, nz;       /* M (number of rows), N (number of columns), and nz(number of non-zeros) */
    int i, *I, *J;
    double *val;

    read_mmf(argc, argv, &I, &J, &val, &M, &N, &nz);

    uint32_t * csc_row = (uint32_t *)malloc(nz     * sizeof(uint32_t));
    uint32_t * csc_col = (uint32_t *)malloc((N + 1) * sizeof(uint32_t));
    uint32_t isOneBased = 0;

    coo2csc(csc_row, csc_col, (uint32_t *)I, (uint32_t *)J, nz, M, isOneBased);

    double serial_time_needed = serial_implementation(csc_row, csc_col, N, nz);
    printf("Time needed to compute C = A.*(A*A) serial: %f seconds\n", serial_time_needed);

    double cilk_time_needed = cilk_implementation(csc_row, csc_col, N, nz);
    printf("Time needed to compute C = A.*(A*A) parallel with cilk: %f seconds\n", cilk_time_needed);  

    printf("%f seconds cilk is faster than serial\n", serial_time_needed-cilk_time_needed);

    return 0;
}
