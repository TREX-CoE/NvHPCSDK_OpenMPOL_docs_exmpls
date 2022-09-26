/*
Build with ./build.sh
*/
#include "includes.h"

int main() {
    // Init cublas & allocate arrays
    #include "alloc.c"

    // Init arrays
    #include "init.c"

    // Print arrays & pointers to check
    printf("Initial values of A, B and C:\n");
    print_m(A, M, N, ldA, "A");
    print_m(B, M, N, ldB, "B");
    print_m(C, M, N, ldC, "C before");

//  printf("Host-pointer address of C    = %p\n", C);
//  printf("Host-pointer address of T1   = %p\n", T1);
//  printf("Host-pointer address of T2   = %p\n\n", T2);

    /*
    * Perform on device
    * 1. T1 <- A - 1
    * 2. T2 <- B + 1
    * 3. C <- C - T1 * T2  in cublas using device pointers
    *
    * Perform on host
    * 4. diag(C) <- diag(C) + 1
    *
    * Perform on device
    * 5. diag(C) <- diag(C) + 1
    */

    // Structured version
//    #include "structured.c"

    // Un-structured version
    #include "unstructured.c"

    printf("Final value of C:\n");
    print_m(C, M, N, ldC, "C after");

    // De-init cublas and free memory
    #include "dealloc.c"

    return 0;
}
