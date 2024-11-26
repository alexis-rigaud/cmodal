/****
  ceig.c (find eigenvalue of a square non-symmetric real matrix)

  to build : (under octave or matlab) for MACOS
   - setenv("LDFLAGS","-framework Accelerate -L/opt/homebrew/Cellar/octave//9.2.0_1/lib/octave/9.2.0/")
   - setenv("CFLAGS","-I/opt/homebrew/Cellar/octave/9.2.0_1/include/octave-9.2.0/octave/")
   - clear ceig; mex -Ilib/linag -Llib/linalg -llinalg src/ceig.c

  matlab code :
   function [D] = ceigen(A)
   %% find eigenvalues of A
   [D] = eig(A);
   end

****/

#include <mex.h>
//#include <gsl/gsl_matrix.h>
//#include <gsl/gsl_eigen.h>

#include "linalg/vector.h"
#include "linalg/matrix.h"
#include "linalg/eigen.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    mxArray *a_in, *d_out;
    const mwSize *dims;
    double *a, *d;
    int rows, cols;

    // Get dimensions of input array:
    dims = mxGetDimensions(prhs[0]);
    rows = (int) dims[0];
    cols = (int) dims[1];

    // Output array:
    d_out = plhs[0] = mxCreateDoubleMatrix(rows, cols, mxREAL);

    // Access the contents of the input and output arrays:
    d = a = mxGetPr(prhs[0]);
    d = mxGetPr(d_out);

    // test the input matrix A is square
    if (rows != cols)   mexErrMsgIdAndTxt("ceig()",
           "Input matrix shall be square");
    size_t n = rows;

    // Allocate a GSL matrix
    //gsl_matrix * gsl_a = gsl_matrix_alloc(n, n);
    //for (int i = 0; i < n*n; i++) {
    //    gsl_a->data[i] = a[i];
    //}

    struct matrix* M = matrix_from_array(a, n, n);
    struct vector* res = eigen_solve_eigenvalues(M, 0.0001, 100);


    // Allocate workspace and compute the eigenvalue
    //gsl_eigen_nonsymm_workspace * w = gsl_eigen_nonsymm_alloc(n);
    //gsl_vector_complex *dummy = gsl_vector_complex_alloc (n);
    //gsl_eigen_nonsymm(gsl_a, dummy, w); // out in diag(A)

    // write into D
    for (int i = 0; i < n; i++) {
        d[i + i*n] = VECTOR_IDX_INTO(res, i);
    }

    // free allocated memory
    matrix_free(M); vector_free(res);

;
}