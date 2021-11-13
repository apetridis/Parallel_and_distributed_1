/*********************************************************************
 * File: myhelpers.h
 * 
 * Author: Alexandros Petridis
 * Date: September 2021
 *
 * Description: Header file for serial implementation and helpers
 ********************************************************************/
#ifndef __COVIDTRACE_H__
#define __COVIDTRACE_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>     /* for uint32_t      */
#include <sys/time.h>   /* for timespec      */
#include <time.h>       /* for clock_gettime */
#include "mmio.h"

/********************************************************************************
 * Function: coo2csc
 * 
 * Description: This function converts COO to CSC cordinates of a matrix
 * 
 * Return: nothing
 * 
 * Source: https://github.com/AUTh-csal/pds-codebase/blob/main/coo2csc/coo2csc.c
 * 
 * ******************************************************************************/
void coo2csc(
    uint32_t       * const row,       /*!< CSC row start indices */
    uint32_t       * const col,       /*!< CSC column indices */
    uint32_t const * const row_coo,   /*!< COO row indices */
    uint32_t const * const col_coo,   /*!< COO column indices */
    uint32_t const         nnz,       /*!< Number of nonzero elements */
    uint32_t const         n,         /*!< Number of rows/columns */
    uint32_t const         isOneBased /*!< Whether COO is 0- or 1-based */
);

/********************************************************************************
 * Function: reaf_mmf
 * 
 * Description: This function reads a matrix from a .mtx file
 * 
 * Return: 0 if matrix readed, number of error if some error came up
 * 
 * ******************************************************************************/
int read_mmf(
    int argc, char *argv[],     /* Read matrix from Matrix-Market-file */
    int **I_,                   /* Row matrix */
    int **J_,                   /* Column matrix */
    double **val_,              /* Values matrix */
    int *M_,                    /* Number of rows */
    int *N_,                    /* Number of columns */
    int *nz_                    /* Number of non-zero values */
);

/********************************************************************************
 * Function: binarySearch
 * 
 * Description: A recursive binary search
 * 
 * Return: location of x in given array arr[l..r] is present, otherwise -1
 * 
 * Source: https://www.geeksforgeeks.org/binary-search/
 *  
 * ******************************************************************************/
int mybinarySearch(int arr[], int l, int r, int x);

/********************************************************************************
 * Function: serial_implementation
 * 
 * Description: This function implements in serial the result C = A.*(A*A)
 * 
 * Return: Time of implementation
 * 
 * ******************************************************************************/
double serial_implementation(
    uint32_t       * const row,
    uint32_t       * const col,
    uint32_t const         N,
    uint32_t const         nz
);

#endif /* __MYHELPERS_H__ */