free(A);
free(B);
free(C);
free(T1);
free(T2);
cublasDestroy(b_handle);
cusolverDnDestroy(s_handle);
