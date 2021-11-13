/*********************************************************************
 * File: myopenmp.h
 * 
 * Author: Alexandros Petridis
 * Date: September 2021
 *
 * Description: Header file for OpenMP use in functions
 ********************************************************************/

#ifndef __MYOPENMP_H__
#define __MYOPENMP_H__

#include <stdio.h>
#include <stdlib.h>
#include "myhelpers.h"
#include <stdint.h>     /* for uint32_t      */
#include <sys/time.h>   /* for timespec      */
#include <time.h>       /* for clock_gettime */
#include <omp.h>

/********************************************************************************
 * Function: mp_implementation
 * 
 * Description: This function implements in parallel the result C = A.*(A*A)
 * with help of open_mp library
 * 
 * Return: Time of implementation
 * 
 * ******************************************************************************/
double mp_implementation(
    uint32_t       * const row,
    uint32_t       * const col,
    uint32_t const         N,
    uint32_t const         nz
);

#endif /* __MYOPENMP_H__ */