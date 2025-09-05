#include <stdio.h>
// #include "sum.h"
#include <dlfcn.h>
int main() {
    // printf("%d\n", sum(1, 2));
    void *handle = dlopen("./libsum.so", RTLD_LAZY);
    if(!handle) {
        return 1;
        // exit(1);
    }
    dlerror();
    int (*sum)(int,int);
    *(void**) (&sum) = dlsym(handle, "sum");

    // char*error = 
    
    printf("%d\n", sum(1, 2));
    dlclose(handle);
    return 0;


}
