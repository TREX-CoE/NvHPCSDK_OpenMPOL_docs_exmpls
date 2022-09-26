int cusolverError = 0;

// Init cusolver
cusolverDnHandle_t s_handle = init_cusolver();

// Allocate arrays
uint16_t M = 3;
uint16_t N = 3;
double determinant;
int* pivot   = calloc(1, sizeof *pivot * M);  // M = 3
double* A    = calloc(1, sizeof *A * M * N);  // M x N = 3 x 3

// Allocate cusolver workspace
int workspace_size = 0;
int* info = NULL;
cusolverDnDgetrf_bufferSize(s_handle, M, N, A, N, &workspace_size);
printf("Size of 'workspace' = %d\n--------------------------\n\n");
double* workspace = calloc(1, sizeof *workspace * workspace_size);
