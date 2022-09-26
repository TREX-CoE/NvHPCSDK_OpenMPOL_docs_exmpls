#pragma omp target enter data map(to:    A[0:M*N]) \
                              map(alloc: pivot[0:M], \
                                         workspace[0:workspace_size], \
                                         Ainv[0:M*N])

#pragma omp target data use_device_ptr(A, workspace, pivot, Ainv)
{ // Begin device region with valid device pointers A, workspace, pivot, Ainv
    cusolverError = cusolverDnDgetrf(s_handle, M, N, A, N, workspace, pivot, info); // Compute PA = LU: store [U,L] in A and P in pivot
    #pragma omp target teams distribute parallel for // Prep Ainv as I as RHS of AX=I
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            Ainv[i * ldAinv + j] = (i == j);
        }
    }
    cusolverError = cusolverDnDgetrs(s_handle, CUBLAS_OP_N, M, M, A, ldA, pivot, Ainv, ldAinv, info);
} // End device region with valid device pointers A, workspace, pivot, Ainv
#pragma omp target update from(Ainv[0:M*N])
#pragma omp target exit data map(delete: A[0:M*N], Ainv[0:M*N], pivot[0:M], workspace[0:workspace_size])
