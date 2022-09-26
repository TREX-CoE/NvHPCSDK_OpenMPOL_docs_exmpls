#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <cublas_v2.h>
#include <cusolverDn.h>
#include <cusolver_common.h>
#include <cuda_runtime_api.h>

void minikernel(double* T1, double* T2,
    double* A, double* B,
    uint16_t M, uint16_t N) {
  printf("Device-pointer address of T1 in minikernel = %p\n", T1);
  printf("Device-pointer address of T2 in minikernel = %p\n\n", T2);
  #pragma omp target teams distribute parallel for
  for (size_t i = 0; i < M * N; i++) {
    T1[i] = A[i] - 1;
    T2[i] = B[i] + 1;
  }
}

cublasHandle_t init_cublas() {
    cublasHandle_t handle;
    if (cublasCreate(&handle) != CUBLAS_STATUS_SUCCESS) {
        fprintf(stdout, "cuBLAS initialization failed!\n");
        exit(EXIT_FAILURE);
    }
    return handle;
}

cusolverDnHandle_t init_cusolver() {
    cusolverDnHandle_t handle;
    if (cusolverDnCreate(&handle) != CUSOLVER_STATUS_SUCCESS) {
        fprintf(stdout, "cuSOLVER initialization failed!\n");
        exit(EXIT_FAILURE);
    }
    return handle;
}

void print_m(const double* mat, uint16_t m, uint16_t n, uint16_t ldm, char* name)
{
  printf("%s = \n", name);
  for (uint16_t i = 0; i < m; ++i)
  {
    for (uint16_t j = 0; j < n; ++j)
    {
      printf("%9.3f ", mat[i * ldm + j]);
    }
    printf("\n");
  }
  printf("\n");
}

void print_m_t(const double* mat, uint16_t m, uint16_t n, uint16_t ldm, char* name)
{
  printf("%s = \n", name);
  for (uint16_t i = 0; i < m; ++i)
  {
    for (uint16_t j = 0; j < n; ++j)
    {
      printf("%11.5f ", mat[j * ldm + i]);
    }
    printf("\n");
  }
  printf("\n");
}

void transpose(double* a, uint16_t lda, double *b, uint16_t ldb, uint16_t m, uint16_t n)
{
  for(uint16_t i = 0; i < m; i++)
  {
    for( uint16_t j = 0; j < n; j++)
    {
      b[j * ldb + i] = a[i * lda + j];
    }
  }
}
