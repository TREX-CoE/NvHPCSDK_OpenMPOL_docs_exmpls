int cublasError;
double alpha;
double beta;

// Init cublas
cublasHandle_t b_handle = init_cublas();

// Init cusolver
cusolverDnHandle_t s_handle = init_cusolver();

// Allocate arrays
uint16_t M = 2;
uint16_t N = 2;
uint16_t K = 2;
double* A  = calloc(1, sizeof *A * M * K);  // M x K = 2 x 2
double* B  = calloc(1, sizeof *B * K * N);  // K x N = 2 x 2
double* C  = calloc(1, sizeof *C * M * N);  // M x N = 2 x 2
double* T1 = calloc(1, sizeof *T1 * M * N);  // M x N = 2 x 2
double* T2 = calloc(1, sizeof *T2 * M * N);  // M x N = 2 x 2
