/*********************************************************************
 * File: myhelpers.c
 * 
 * Author: Alexandros Petridis
 * Date: September 2021
 *
 * Description: Implementations of header file myhelpers.h
 ********************************************************************/

#include "myhelpers.h"

void coo2csc(
    uint32_t       * const row,       /*!< CSC row start indices */
    uint32_t       * const col,       /*!< CSC column indices */
    uint32_t const * const row_coo,   /*!< COO row indices */
    uint32_t const * const col_coo,   /*!< COO column indices */
    uint32_t const         nnz,       /*!< Number of nonzero elements */
    uint32_t const         n,         /*!< Number of rows/columns */
    uint32_t const         isOneBased /*!< Whether COO is 0- or 1-based */
) {

    // ----- cannot assume that input is already 0!
    for (uint32_t l = 0; l < n+1; l++) col[l] = 0;


    // ----- find the correct column sizes
    for (uint32_t l = 0; l < nnz; l++)
        col[col_coo[l] - isOneBased]++;

    // ----- cumulative sum
    for (uint32_t i = 0, cumsum = 0; i < n; i++) {
        uint32_t temp = col[i];
        col[i] = cumsum;
        cumsum += temp;
    }
    col[n] = nnz;
    // ----- copy the row indices to the correct place
    for (uint32_t l = 0; l < nnz; l++) {
        uint32_t col_l;
        col_l = col_coo[l] - isOneBased;

        uint32_t dst = col[col_l];
        row[dst] = row_coo[l] - isOneBased;

        col[col_l]++;
    }
    // ----- revert the column pointers
    for (uint32_t i = 0, last = 0; i < n; i++) {
        uint32_t temp = col[i];
        col[i] = last;
        last = temp;
    }

}

int read_mmf(
    int argc, char *argv[],     /* Read matrix from Matrix-Market-file */
    int **I_,                   /* Row matrix */
    int **J_,                   /* Column matrix */
    double **val_,              /* Values matrix */
    int *M_,                    /* Number of rows */
    int *N_,                    /* Number of columns */
    int *nz_                    /* Number of non-zero values */
) {
    
    int ret_code;
    MM_typecode matcode;
    FILE *f;
    int M, N, nz;
    double *val;
    int *I, *J;

    int i;

    if (argc < 2)
	{
		fprintf(stderr, "Usage: %s [martix-market-filename]\n", argv[0]);
		exit(1);
	}
    else    
    { 
        if ((f = fopen(argv[1], "r")) == NULL) 
            exit(1);
    }

    if (mm_read_banner(f, &matcode) != 0)
    {
        printf("Could not process Matrix Market banner.\n");
        exit(1);
    }


    /*  This is how one can screen matrix types if their application */
    /*  only supports a subset of the Matrix Market data types.      */

    if (mm_is_complex(matcode) && mm_is_matrix(matcode) && 
            mm_is_sparse(matcode) )
    {
        printf("Sorry, this application does not support ");
        printf("Market Market type: [%s]\n", mm_typecode_to_str(matcode));
        exit(1);
    }

    /* find out size of sparse matrix .... */

    if ((ret_code = mm_read_mtx_crd_size(f, &M, &N, &nz)) !=0)
        exit(1);
    


    /* reseve memory for matrices */

    I = (int *) malloc(nz * sizeof(int));
    J = (int *) malloc(nz * sizeof(int));
    val = (double *) malloc(nz * sizeof(double));
 

    /* NOTE: when reading in doubles, ANSI C requires the use of the "l"  */
    /*   specifier as in "%lg", "%lf", "%le", otherwise errors will occur */
    /*  (ANSI C X3.159-1989, Sec. 4.9.6.2, p. 136 lines 13-15)            */

    for (i=0; i<nz; i++)
    {
        if(fscanf(f, "%d %d\n", &I[i], &J[i]) == 2){
            val[i]=1;
            I[i]--;  /* adjust from 1-based to 0-based */
            J[i]--;
        }
        else exit(1);
    }

    if (mm_is_symmetric(matcode)) { /* If matrix is symmetric Market-Matrix returns only half of values */

        I = (int *) realloc(I, nz * sizeof(int)*2);
        J = (int *) realloc(J, nz * sizeof(int)*2);
        val = (double *) realloc(val, nz * sizeof(double)*2);

        for (i=0; i<nz; i++) {
            val[nz+i] = val[i];
            I[nz+i] = J[i];
            J[nz+i] = I[i];
        }

        nz = 2*nz;

    }

    *val_ = val;
    *I_ = I;
    *J_ = J;  

    *M_ = M;
    *N_ = N;
    *nz_ = nz;    

    if (f !=stdin) fclose(f);
    return 0;
}

int mybinarySearch(int arr[], int l, int r, int x){

    if (r >= l) {
        int mid = l + (r - l) / 2;
 
        // If the element is present at the middle
        // itself
        if (arr[mid] == x)
            return mid;
 
        // If element is smaller than mid, then
        // it can only be present in left subarray
        if (arr[mid] > x)
            return mybinarySearch(arr, l, mid - 1, x);
 
        // Else the element can only be present
        // in right subarray
        return mybinarySearch(arr, mid + 1, r, x);
    }
 
    // We reach here when element is not
    // present in array
    return -1;
}

double serial_implementation(
    uint32_t       * const row,
    uint32_t       * const col,
    uint32_t const         N,
    uint32_t const         nz
) {
    int i;
    struct timespec start_time;
    struct timespec end_time;    

    int *C = (int *) malloc(nz * sizeof(int));  /* C = A.*(A*A) where A matrix from .mtx file*/
    for (i=0; i<N; i++)
        C[i] = 0;
   
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    for (i=0; i<N; i++)
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
