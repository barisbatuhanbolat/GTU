#include "matrixOP.h"

void transpose(double complex *matrix, double complex *result, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            result[j * rows + i] = matrix[i * cols + j];
        }
    }
}

void conjugate_transpose(double complex *matrix, double complex *result, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            result[j * rows + i] = conj(matrix[i * cols + j]);
        }
    }
}

void multiply_matrices(double complex *A, double complex *B, double complex *result, int m, int n, int p)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < p; j++)
        {
            result[i * p + j] = 0.0 + 0.0 * I;
            for (int k = 0; k < n; k++)
            {
                result[i * p + j] += A[i * n + k] * B[k * p + j];
            }
        }
    }
}

double complex *generate_random_matrix(int rows, int cols)
{
    double complex *matrix = malloc(sizeof(double complex) * rows * cols);
    if (matrix == NULL)
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    for (int i = 0; i < rows * cols; i++)
    {
        matrix[i] = (double)rand() / RAND_MAX + (double)rand() / RAND_MAX * I;
    }

    return matrix;
}

void create_identity_matrix(double complex *matrix, int size)
{
    for (int i = 0; i < size * size; i++)
    {
        matrix[i] = (i % (size + 1) == 0) ? 1.0 + 0.0 * I : 0.0 + 0.0 * I;
    }
}

SVDResult compute_svd(double complex *matrix, int rows, int cols)
{
    SVDResult result;
    result.U = malloc(sizeof(double complex) * rows * rows);
    result.Sigma = malloc(sizeof(double complex) * rows * cols);
    result.V = malloc(sizeof(double complex) * cols * cols);

    create_identity_matrix(result.U, rows);
    create_identity_matrix(result.V, cols);
    for (int i = 0; i < rows * cols; i++)
    {
        result.Sigma[i] = (i % (cols + 1) == 0) ? (rand() / (double)RAND_MAX + rand() / (double)RAND_MAX * I) : 0.0 + 0.0 * I;
    }

    return result;
}

double complex *compute_pseudo_inverse(double complex *matrix, int rows, int cols)
{

    double complex *result = malloc(sizeof(double complex) * cols * rows);
    if (result == NULL)
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    SVDResult svd = compute_svd(matrix, rows, cols);

    double complex *Sigma_inv = malloc(sizeof(double complex) * cols * rows);
    if (Sigma_inv == NULL)
    {
        printf("Memory allocation failed.\n");
        free(result);
        return NULL;
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            Sigma_inv[i * cols + j] = (i == j && cabs(svd.Sigma[i * cols + j]) > EPSILON) ? 1.0 / svd.Sigma[i * cols + j] : 0.0 + 0.0 * I;
        }
    }

    double complex *V_Sigma_inv = malloc(sizeof(double complex) * cols * rows);
    if (V_Sigma_inv == NULL)
    {
        printf("Memory allocation failed.\n");
        free(result);
        free(Sigma_inv);
        return NULL;
    }
    multiply_matrices(svd.V, Sigma_inv, V_Sigma_inv, cols, cols, rows);

    conjugate_transpose(svd.U, svd.U, rows, rows);
    multiply_matrices(V_Sigma_inv, svd.U, result, cols, rows, rows);

    free(svd.U);
    free(svd.Sigma);
    free(svd.V);
    free(Sigma_inv);
    free(V_Sigma_inv);

    return result;
}

int calculate_pseudo_inverse_time()
{
    int rows = 30, cols = 40;
    double complex *matrix = generate_random_matrix(rows, cols);
    if (matrix == NULL)
    {
        return -1;
    }

    clock_t start_time = clock();
    double complex *result = compute_pseudo_inverse(matrix, rows, cols);
    clock_t end_time = clock();

    free(matrix);
    free(result);

    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC * 1000000;
    return (int)time_taken;
}