#pragma omp target enter data map(to: A[0:M*K], B[0:K*N], C[0:M*N]) \
                              map(alloc: T1[0:M*N], T2[0:M*N])

for (size_t i = 0; i < M * N; i++) {
    T1[i] = A[i] - 1;
    T2[i] = B[i] + 1;
}
#pragma omp target update to(T1[0:M*N], T2[0:M*N])


#pragma omp target data use_device_ptr(T1, T2, C)
{
//        printf("Device-pointer address of C  = %p\n", C);
//        printf("Device-pointer address of T1 = %p\n", T1);
//        printf("Device-pointer address of T2 = %p\n\n", T2);
    alpha = -1.0, beta = 1.0;
    cublasError = cublasDgemm(b_handle,
                              CUBLAS_OP_N, CUBLAS_OP_N,
                              N, M, K,
                              &alpha, T2, ldT2, T1, ldT1,
                              &beta, C, ldC);
}
if (cublasError != 0) return cublasError; // branching in/out of accelerator data regions only allowed with unstructured regions
#pragma omp target update from(C[0:M*N])

// On host
C[0] += 1.0f, C[3] += 1.0f;
#pragma omp target update to(C[0:M*N])

// On device
#pragma omp target
C[0] += 1.0f, C[3] += 1.0f;
#pragma omp target update from(C[0:M*N])

#pragma omp target exit data map(delete: A[0:M*K], B[0:K*N], C[0:M*N], T1[0:M*N], T2[0:M*N])
