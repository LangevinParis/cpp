#include <cuda.h>
#include <iostream>

using namespace std;


// Several kernels which dump the values of index, threadIdx.x, blockDim.x, blockIdx.x
__global__ void kernel_idx(int *a) {a[threadIdx.x + blockDim.x * blockIdx.x] = threadIdx.x + blockDim.x * blockIdx.x;}
__global__ void kernel_blockdim(int *a) {a[threadIdx.x + blockDim.x * blockIdx.x] = blockDim.y;}
__global__ void kernel_threadIdx(int *a) {a[threadIdx.x + blockDim.x * blockIdx.x] = threadIdx.x;}
__global__ void kernel_blockIdx(int *a) {a[threadIdx.x + blockDim.x * blockIdx.x] = blockIdx.x;}

// Here, the unique thread index is: threadIdx.x + blockDim.x * blockIdx.x;


int main(int argc, char *argv[]) {

  // Init the grid size
  int grid_size = 3;int block_size = 4;
  const int N = grid_size*block_size;

  // Allocate memory on the Device
  int* d_a; cudaMalloc((void **) &d_a, N * sizeof(int));

  // Get the wanted index
	kernel_blockdim<<<grid_size, block_size>>>(d_a);

  // Copy data from Device to Host
  int h_a[N]; cudaMemcpy(h_a, d_a, N * sizeof(int), cudaMemcpyDeviceToHost);

  // Display the blockdim adress:
  cout<<"\nblockdim.x\t= "; for (int i = 0; i < N; i++) {std::cout << h_a[i] << "\t";}

  // Get the wanted index
	kernel_threadIdx<<<grid_size, block_size>>>(d_a);

  // Copy data from Device to Host
	cudaMemcpy(h_a, d_a, N * sizeof(int), cudaMemcpyDeviceToHost);

  // Display the blockdim adress:
  cout<<"\nthreadIdx.x\t= "; for (int i = 0; i < N; i++) {std::cout << h_a[i] << "\t";}

  // Get the wanted index
	kernel_blockIdx<<<grid_size, block_size>>>(d_a);

  // Copy data from Device to Host
	cudaMemcpy(h_a, d_a, N * sizeof(int), cudaMemcpyDeviceToHost);

  // Display the blockdim adress:
  cout<<"\nblockIdx.x\t= ";for (int i = 0; i < N; i++) {std::cout << h_a[i] << "\t";}

  // Get the wanted index
	kernel_idx<<<grid_size, block_size>>>(d_a);

  // Copy data from Device to Host
	cudaMemcpy(h_a, d_a, N * sizeof(int), cudaMemcpyDeviceToHost);

  // Display the blockdim adress:
  cout<<"\nglobalIdx.x\t= "; for (int i = 0; i < N; i++) {std::cout << h_a[i] << "\t";}
}
