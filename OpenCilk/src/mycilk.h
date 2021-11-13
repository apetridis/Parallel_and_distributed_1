/*********************************************************************
 * File: mycilk.h
 * 
 * Author: Alexandros Petridis
 * Date: September 2021
 *
 * Description: Header file for OpenCilk use in functions
 ********************************************************************/

#ifndef __MYCILK_H__
#define __MYCILK_H__

#include <stdio.h>
#include <stdlib.h>
#include "myhelpers.h"
#include <stdint.h>     /* for uint32_t      */
#include <sys/time.h>   /* for timespec      */
#include <time.h>       /* for clock_gettime */
#include <cilk/cilk.h>

/********************************************************************************
 * Function: silk_implementation
 * 
 * Description: This function implements in parallel the result C = A.*(A*A)
 * with help of cilk library
 * 
 * Return: Time of implementation
 * 
 * ******************************************************************************/
double cilk_implementation(
    uint32_t       * const row,
    uint32_t       * const col,
    uint32_t const         N,
    uint32_t const         nz
);

#endif /* __MYCILK_H__ */
