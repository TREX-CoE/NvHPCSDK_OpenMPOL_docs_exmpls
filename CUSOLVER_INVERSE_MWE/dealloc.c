free(A);
free(pivot);
free(workspace);
free(Ainv);
cusolverDnDestroy(s_handle);
