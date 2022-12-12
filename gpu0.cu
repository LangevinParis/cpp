#include <cstdio>
#include <cuda.h>  //Useless?

#include <iostream>
using namespace std;

__global__ void cuda_hello(){
    printf("Hello World from GPU!\n"); // Does not print...

}

int main() {

    cuda_hello<<<1,1>>>(); 
    
    cout << "Hello, World from CPU! This can be compiled by nvcc\n";

    return 0;
}
