free(A);
free(pivot);
free(workspace);
cusolverDnDestroy(s_handle);
