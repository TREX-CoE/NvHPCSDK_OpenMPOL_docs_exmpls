#pragma omp target enter data map(to:    A[0:M*N]) \
                              map(alloc: pivot[0:M], \
                                         workspace[0:workspace_size], \
                                         Ainv[0:M*N])

#pragma omp target data use_device_ptr(A, workspace, pivot) // compute C ON DEVICE
{
    cusolverError = cusolverDnDgetrf(s_handle, M, N, A, N, workspace, pivot, info);
}
// Not necessary
#pragma omp target update from(A[0:M*N], pivot[0:M])
print_dm_t(A, M, N, ldA, "A (overwritten by [U, L])");
print_im(pivot, 1, M, M, "Pivot indices");
// Not necessary

// Prepare Ainv by initializing it to the identity matrix 'I' as a RHS to solve
#pragma omp target teams distribute parallel for
for (int i = 0; i < M; ++i) {
    for (int j = 0; j < N; ++j) {
        Ainv[i * ldAinv + j] = (i == j);
    }
}

#pragma omp target data use_device_ptr(A, pivot, Ainv)
{
    cusolverError = cusolverDnDgetrs(s_handle, CUBLAS_OP_N, M, M, A, ldA, pivot, Ainv, ldAinv, info);
}
#pragma omp target update from(Ainv[0:M*N])

#pragma omp target exit data map(delete: A[0:M*N], Ainv[0:M*N], pivot[0:M], workspace[0:workspace_size])
