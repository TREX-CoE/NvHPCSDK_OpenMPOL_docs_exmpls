#pragma omp target enter data map(to:    A[0:M*N]) \
                              map(alloc: pivot[0:M], workspace[0:workspace_size])
#pragma omp target data use_device_ptr(A, workspace, pivot)
{ // Begin device region with valid device pointers A, workspace, pivot
    cusolverError = cusolverDnDgetrf(s_handle, M, N, A, N, workspace, pivot, info); // Compute PA = LU: store [U,L] in A and P in pivot
    bool swap = false; uint32_t j = 0;
    #pragma omp target teams distribute parallel for reduction(+: j) reduction(*: determinant)
    for (uint32_t i = 0; i < M; i++)
    {
        swap = (bool)(pivot[i] - (i + 1));         // swap = {0->false: no swap, >0->true: swap}
        j += (uint32_t)swap;                       // count # of swaps
        determinant *= A[i * (M + 1)];             // prod. of diag elm. of A
    }
    if ((j & 1) != 0) determinant = -determinant;  // multiply det with -1 if # of swaps is odd
} // End device region with valid device pointers A, workspace, pivot
#pragma omp target exit data map(delete: A[0:M*N], pivot[0:M], workspace[0:workspace_size])
