/* cmtimes.c
  (c) A. Rigaud, 2024

  Matrix multiply.
  [D] = cmtimes(A, B);

  this is
  for i = [1.. col A]
  for j = [1.. row B]
  C(i,j) = A(i,:)*B(:,j)


 */

#include <mex.h>
#include <mxarray.h>

#include "linalg/vector.h"
#include "linalg/matrix.h"
#include "linalg/eigen.h"

#define ROW 0
#define COL 1

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    mxArray *a_in, *b_in, *d_out;
    const mwSize *a_dims, *b_dims;
    double *a, *b, *d;

    // test number of arguments
    if (nrhs != 2)  mexErrMsgIdAndTxt("cmtimes()", "Two input allowed");
    if (nlhs != 1)  mexErrMsgIdAndTxt("cmtimes()", "One output allowed");

    // Get dimensions of input array A and B
    a_dims = mxGetDimensions(prhs[0]);
    b_dims = mxGetDimensions(prhs[1]);

    // Deduce output dims after the mult
    int rows = (int) a_dims[ROW];
    int cols = (int) b_dims[COL];

    // Create output matrix D
    plhs[0] = mxCreateDoubleMatrix(rows, cols, mxREAL);

    // Access the contents of the input/outputs arrays
    a = mxGetPr(prhs[0]);
    b = mxGetPr(prhs[1]);
    d = mxGetPr(plhs[0]);

    // read the inputs matrix A, B
    struct matrix* m_left   = matrix_from_matlab(a, a_dims[ROW], a_dims[COL]);
    struct matrix* m_right  = matrix_from_matlab(b, b_dims[ROW], b_dims[COL]);

    // C = A*B
    struct matrix* m_output = matrix_multiply(m_left, m_right);

    // Write back into D
    matrix_to_matlab(d, m_output);

    // free allocated memory
    matrix_free_many(3, m_left, m_right, m_output);
}
