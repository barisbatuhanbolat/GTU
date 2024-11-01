#ifndef MATRIXOP_H
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <math.h>
#include <semaphore.h>
#include <complex.h>
#include <time.h>
typedef struct
{
    double complex *U;
    double complex *Sigma;
    double complex *V;
} SVDResult;

#define ROWS 30
#define COLS 40
#define EPSILON 1e-10

void transpose(double complex *matrix, double complex *result, int rows, int cols);
void conjugate_transpose(double complex *matrix, double complex *result, int rows, int cols);
void multiply_matrices(double complex *A, double complex *B, double complex *result, int m, int n, int p);
double complex *generate_random_matrix(int rows, int cols);
void create_identity_matrix(double complex *matrix, int size);
SVDResult compute_svd(double complex *matrix, int rows, int cols);
double complex *compute_pseudo_inverse(double complex *matrix, int rows, int cols);
int calculate_pseudo_inverse_time();

#endif