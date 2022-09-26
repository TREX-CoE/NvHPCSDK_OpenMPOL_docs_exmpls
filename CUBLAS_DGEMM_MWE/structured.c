#pragma omp target data map(to: A[0:M*K], B[0:K*N]) \
                        map(tofrom: C[0:M*N]) \
                        map(alloc: T1[0:M*N], T2[0:M*N])
{ // Start device data region

// minikernel(T1, T2, A, B, M, N); // does the same but "kernalised" (for NSight Compute)
#pragma omp target teams distribute parallel for // execute on device
for (size_t i = 0; i < M * N; i++) {
T1[i] = A[i] - 1;
T2[i] = B[i] + 1;
}
//    #pragma omp target update to(T1[0:M*N], T2[0:M*N]) // OR execute on host, then update to device

#pragma omp target data use_device_ptr(T1, T2, C)
{
//      printf("Device-pointer address of C  = %p\n", C);
//      printf("Device-pointer address of T1 = %p\n", T1);
//      printf("Device-pointer address of T2 = %p\n\n", T2);
alpha = -1.0, beta = 1.0;
int cublasError = cublasDgemm(handle,
                              CUBLAS_OP_N, CUBLAS_OP_N,
                              N, M, K,
                              &alpha, T2, ldT2, T1, ldT1,
                              &beta, C, ldC);
if(cublasError != 0) return cublasError;
}
#pragma omp target update from(C[0:M*N]) // Only needed if C is going to be updated on the
                                         // host before the end of the device data region

// On host
C[0] += 1.0f, C[3] += 1.0f;
#pragma omp target update to(C[0:M*N])

// On device
#pragma omp target
C[0] += 1.0f, C[3] += 1.0f;

} // end device data region
