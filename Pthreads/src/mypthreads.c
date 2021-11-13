/*********************************************************************
 * File: mypthreads.c
 * 
 * Author: Alexandros Petridis
 * Date: September 2021
 *
 * Description: Implementations of header file mypthreads.h
 ********************************************************************/

#include "mypthreads.h"
#include "myhelpers.h"


void* thread_func(void* arg) {   
    func_arg *in = (func_arg *) arg;
    int i = in->i;
    uint32_t N = in->N;
    uint32_t * row = in->row;
    uint32_t * col = in->col;

    for (int k=i*(N/NUMOFTHREADS); k<(i+1)*(N/NUMOFTHREADS); k++)
        for (int j=col[k]; j<col[k+1]; j++)
            for (int q=col[row[j]]; q<col[row[j]+1]; q++)  {
                //pthread_mutex_lock(&mutex);
                if (mybinarySearch((int *)row, j+1, col[k+1]-1, row[q]) != -1) {
                    //pthread_mutex_unlock(&mutex);
                    C[k]++;
                }
                    
            }            
                 
    pthread_exit(NULL);    
}

double pthreads_implementation(
    uint32_t       * const row,
    uint32_t       * const col,
    uint32_t const         N,
    uint32_t const         nz
){
    C = (int *) malloc(nz * sizeof(int));  /* C = A.*(A*A) where A matrix from .mtx file*/
    for (int i=0; i<N; i++)
        C[i] = 0;

    struct timespec start_time;
    struct timespec end_time;    

    pthread_t *threads;
    pthread_attr_t pthread_custom_attr;
    pthread_mutex_init(&mutex, NULL);
    int i;
    func_arg *arg;

    threads = (pthread_t *)malloc(NUMOFTHREADS*sizeof(*threads));
    pthread_attr_init(&pthread_custom_attr);

    arg = (func_arg *) malloc(NUMOFTHREADS*sizeof(func_arg));
    for (i=0; i<NUMOFTHREADS; i++) {
        arg[i].N = N;
        arg[i].row = row;
        arg[i].col = col;
    }    

    clock_gettime(CLOCK_MONOTONIC, &start_time);     

    for (i=0; i<NUMOFTHREADS; i++) {     /* Starting Threads */
        arg[i].i = i;
        if (pthread_create(&threads[i], &pthread_custom_attr, &thread_func, (void *)(&arg[i])) != 0) {
            printf("Error creating #%d thread\n", i);
            exit(1);
        }           
    }

    for (i=0; i<NUMOFTHREADS; i++) {     /* Waits for Threads to finish */
        if (pthread_join(threads[i], NULL) != 0) {
            printf("Error finishing #%d thread\n", i);
            exit(1);
        }            
    }

    clock_gettime(CLOCK_MONOTONIC, &end_time);
    pthread_mutex_destroy(&mutex);

    double time_needed;
    time_needed = (end_time.tv_sec - start_time.tv_sec) * 1e9;
    time_needed = (time_needed + (end_time.tv_nsec - start_time.tv_nsec)) * 1e-9;

    return time_needed;
}