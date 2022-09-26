// Row-major storage
//A[0] = 1, A[1] = 2, A[2] = 3;
//A[3] = 4, A[4] = 5, A[5] = 6;
//A[6] = 7, A[7] = 8, A[8] = 10;

// Col-major storage (enforced by cusolverDnDgetrf(...))
A[0] = 1, A[1] = 4, A[2] = 7;
A[3] = 2, A[4] = 5, A[5] = 8;
A[6] = 3, A[7] = 6, A[8] = 10;

uint16_t ldA  = M;
determinant = 1.0f;
