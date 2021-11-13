/*********************************************************************
 * File: mypthreads.h
 * 
 * Author: Alexandros Petridis
 * Date: September 2021
 *
 * Description: Header file for Pthreads use in functions
 ********************************************************************/

#ifndef __MYPTHREADS_H__
#define __MYPTHREADS_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>     /* for uint32_t      */
#include <sys/time.h>   /* for timespec      */
#include <time.h>       /* for clock_gettime */
#include <pthread.h>

#include <unistd.h>

#define NUMOFTHREADS 80

int *C;
pthread_mutex_t mutex;


typedef struct {
    uint32_t N;
    int i;
    uint32_t * row;
    uint32_t * col;
} func_arg;

void* thread_func(void* arg);

/********************************************************************************
 * Function: mp_implementation
 * 
 * Description: This function implements in parallel the result C = A.*(A*A)
 * with help of open_mp library
 * 
 * Return: Time of implementation
 * 
 * ******************************************************************************/
double pthreads_implementation(
    uint32_t       * const row,
    uint32_t       * const col,
    uint32_t const         N,
    uint32_t const         nz
);

#endif /* __MYPTHREADS_H__ */