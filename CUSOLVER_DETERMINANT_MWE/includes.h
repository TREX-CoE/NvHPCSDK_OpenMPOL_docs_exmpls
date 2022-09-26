#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <cublas_v2.h>
#include <cusolverDn.h>
#include <cusolver_common.h>
#include <cuda_runtime_api.h>

cusolverDnHandle_t init_cusolver() {
    cusolverDnHandle_t handle;
    if (cusolverDnCreate(&handle) != CUSOLVER_STATUS_SUCCESS) {
        fprintf(stdout, "cuSOLVER initialization failed!\n");
        exit(EXIT_FAILURE);
    }
    return handle;
}

void print_dm_t(const double* mat, uint16_t m, uint16_t n, uint16_t ldm, char* name)
{
    printf("%s = \n", name);
    for (uint16_t i = 0; i < m; ++i)
    {
        for (uint16_t j = 0; j < n; ++j)
        {
            printf("%9.4f ", mat[j * ldm + i]);
        }
        printf("\n");
    }
    printf("\n");
}

void print_im(const int* mat, uint16_t m, uint16_t n, uint16_t ldm, char* name)
{
    printf("%s = \n", name);
    for (uint16_t i = 0; i < m; ++i)
    {
        for (uint16_t j = 0; j < n; ++j)
        {
            printf("%d ", mat[i * ldm + j]);
        }
        printf("\n");
    }
    printf("\n");
}

