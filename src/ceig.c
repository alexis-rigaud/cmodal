/* ceig.c

  (c) A. Rigaud, 2024

  Find eigenvalue of a square real matrix (with QR decomposition method)
  [D] = ceig(A); %% find eigenvalues of A

 */

#include <mex.h>

#include "linalg/vector.h"
#include "linalg/matrix.h"
#include "linalg/eigen.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    const mwSize *dims;
    double *a, *d;
    int rows, cols;

    // test number of arguments
    if (nrhs != 1)  mexErrMsgIdAndTxt("ceig()", "One input allowed");
    if (nlhs != 1)  mexErrMsgIdAndTxt("ceig()", "One output allowed");

    // Get dimensions of input array:
    dims = mxGetDimensions(prhs[0]);
    rows = (int) dims[0];
    cols = (int) dims[1];

    // test the input matrix A is square
    if (rows != cols)   mexErrMsgIdAndTxt("ceig()", "Input matrix shall be squared");
    int n = rows;

    // Output array:
    plhs[0] = mxCreateDoubleMatrix(n, 1, mxREAL);

    // Access the contents of the input and output arrays:
    a = mxGetPr(prhs[0]);
    d = mxGetPr(plhs[0]);

    // call the library
    struct matrix* M = matrix_from_matlab(a, n, n);
    struct vector* res = eigen_solve_eigenvalues(M, 0.0001, 100);

    // write back into D
    for (int i = 0; i < n; i++) {
        d[n-1-i] = VECTOR_IDX_INTO(res, i); // flip values order for comparison with matlab
    }

    // free allocated memory
    matrix_free(M); vector_free(res);
}
