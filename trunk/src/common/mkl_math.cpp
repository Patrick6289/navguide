#include "mkl_math.h"

/* c = a x b, where a = [ m x k ], b = [ k x n], c = [ m x n ]
 * 
 * using naive approach
 */
void math_matrix_mult_naive (int m, int n, int k, double *a, double *b, double *c)
{
    for (int row=0;row<m;row++) {
        for (int col=0;col<n;col++) {
            c[row*n+col] = .0;
            double *ptra = a + row*k;
            double *ptrb = b + col;
            for (int kk=0;kk<k;kk++) {
                c[row*n+col] += (*ptra) * (*ptrb);
                ptra++;
                ptrb+=n;
                //a[row*k+kk] * b[kk*n+col];
            }
        }
    }
}

/* c = a x b, where a = [ m x k ], b = [ k x n], c = [ m x n ]
 * 
 * using Intel Math Kernel Library
 */
void math_matrix_mult_mkl (int m, int n, int k, const double *a, const double *b, double *c)
{
    cblas_dgemm (CblasRowMajor, CblasNoTrans, CblasNoTrans, m, n, k, 1.0, a, m, b, k, 0.0, c, m);
}

/* alloc memory for a matrix
 */
double * math_matrix_alloc (int nrows, int ncols)
{
    double *a = (double*)malloc(nrows*ncols*sizeof(double));
    return a;
}

/* free matrix
 */
void math_matrix_free (double *a)
{
    free (a);
}

/* generates a random square matrix of size N x N
 */
double * math_matrix_rand (int N)
{
    double *a = math_matrix_alloc (N, N);

    for (int row=0;row<N;row++) {
        for (int col=0;col<N;col++) {
            a[row*N+col] = 1.0*rand()/RAND_MAX;
        }
    }

    return a;
}

/* matrix multiplication unit testing
 */
void math_matrix_mult_unit_testing ()
{
    double *a, *b, *c;

    for (int N = 500; N <= 2000; N += 100) {

        printf ("N = %d\n", N);

        a = math_matrix_rand (N);
        b = math_matrix_rand (N);

        c = math_matrix_alloc (N, N);

        // naive multiplication
        GTimer *t1 = g_timer_new ();
        math_matrix_mult_naive (N, N, N, a, b, c);
        printf ("naive: %.5f secs.", g_timer_elapsed (t1, NULL));

        // KML multiplication
        GTimer *t2 = g_timer_new ();
        math_matrix_mult_mkl (N, N, N, a, b, c);
        printf ("kml  : %.5f secs.", g_timer_elapsed (t2, NULL));

        math_matrix_free (a);
        math_matrix_free (b);
        math_matrix_free (c);

        g_timer_destroy (t1);
        g_timer_destroy (t2);

    }
}

/* c = a x b, where a = [ m x k ], b = [ k x n], c = [ m x n ]
 * 
 * using naive approach
 */
void math_matrix_mult_naive_float (int m, int n, int k, float *a, float *b, float *c)
{
    for (int row=0;row<m;row++) {
        for (int col=0;col<n;col++) {
            c[row*n+col] = .0;
            float *ptra = a + row*k;
            float *ptrb = b + col;
            for (int kk=0;kk<k;kk++) {
                c[row*n+col] += (*ptra) * (*ptrb);
                ptra++;
                ptrb+=n;
                //a[row*k+kk] * b[kk*n+col];
            }
        }
    }
}

/* c = a x b, where a = [ m x k ], b = [ k x n], c = [ m x n ]
 * 
 * using Intel Math Kernel Library
 */
void math_matrix_mult_mkl_float (int m, int n, int k, const float *a, const float *b, float *c)
{
    cblas_sgemm (CblasRowMajor, CblasNoTrans, CblasNoTrans, m, n, k, 1.0, a, k, b, n, 0.0, c, n);
}

/* alloc memory for a matrix
 */
float * math_matrix_alloc_float (int nrows, int ncols)
{
    float *a = (float*)malloc(nrows*ncols*sizeof(float));
    return a;
}

/* free matrix
 */
void math_matrix_free_float (float *a)
{
    free (a);
}

/* generates a random square matrix of size N x N
 */
float * math_matrix_rand_float (int N, int P)
{
    float *a = math_matrix_alloc_float (N, P);

    for (int row=0;row<N;row++) {
        for (int col=0;col<P;col++) {
            a[row*P+col] = 1.0*rand()/RAND_MAX;
        }
    }

    return a;
}

/* matrix multiplication unit testing
 */
void math_matrix_mult_unit_testing_float ()
{
    float *a, *b, *c;

    for (int N = 500; N <= 2000; N += 100) {

        printf ("N = %d\t", N);

        a = math_matrix_rand_float (N, N);
        b = math_matrix_rand_float (N, N);

        c = math_matrix_alloc_float (N, N);

        // naive multiplication
        GTimer *t1 = g_timer_new ();
        math_matrix_mult_naive_float (N, N, N, a, b, c);
        printf ("naive: %.5f secs. ", g_timer_elapsed (t1, NULL));

        // KML multiplication
        GTimer *t2 = g_timer_new ();
        math_matrix_mult_mkl_float (N, N, N, a, b, c);
        printf ("kml  : %.5f secs.\n", g_timer_elapsed (t2, NULL));

        math_matrix_free_float (a);
        math_matrix_free_float (b);
        math_matrix_free_float (c);

        g_timer_destroy (t1);
        g_timer_destroy (t2);

    }
}

/* matrix multiplication unit testing
 */
void math_matrix_mult_unit_testing_float_2 ()
{
    float *a, *b, *c;
    int M = 500;
    int N = 20000;
    int K = 128;

    a = math_matrix_rand_float (M, K);
    b = math_matrix_rand_float (K, N);

    c = math_matrix_alloc_float (M, N);

    // naive multiplication
    GTimer *t1 = g_timer_new ();
    math_matrix_mult_naive_float (M, N, K, a, b, c);
    printf ("naive: %.5f secs. ", g_timer_elapsed (t1, NULL));

    // KML multiplication
    GTimer *t2 = g_timer_new ();
    math_matrix_mult_mkl_float (M, N, K, a, b, c);
    printf ("kml  : %.5f secs.\n", g_timer_elapsed (t2, NULL));

    math_matrix_free_float (a);
    math_matrix_free_float (b);
    math_matrix_free_float (c);

    g_timer_destroy (t1);
    g_timer_destroy (t2);
}

