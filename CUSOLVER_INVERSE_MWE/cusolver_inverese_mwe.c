/*
-----------------------------
 Build with: ./build.sh
 Clean with: ./build.sh clean
-----------------------------

Compute inverse of

    1  2   3
A = 4  5   6
    7  8  10

via LU-decomposition (cusolverDnDgetrf)

    7.0000  8.0000  10.0000
U = 0.0000  0.8571   1.5714
    0.0000  0.0000  -0.5000

    0.0000  0.0000   0.0000
L = 0.1429  0.0000   0.0000
    0.5714  0.5000   0.0000

Pivot indices = 3, 3, 3

and solving AX=I (cusolverDnDgetrs)

       -0.6667  -1.3333   1.0000
Ainv = -0.6667   3.6667  -2.0000
        1.0000  -2.0000   1.0000
*/

#include "includes.h"

int main() {
    // Init cublas & allocate arrays
    #include "alloc.c"

    // Init arrays
    #include "init.c"

    // Print A
    print_dm_t(A, M, N, ldA, "A (initial)");

    // Structured version
    #include "structured_lean.c"

    // Un-structured version
//    #include "unstructured_lean.c"

    // Print resulting Ainv
    print_dm_t(Ainv, M, N, ldAinv, "inverse of A");

    // De-init cublas and free memory
    #include "dealloc.c"

    return 0;
}
