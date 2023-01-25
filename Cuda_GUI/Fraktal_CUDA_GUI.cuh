#include "cuda_runtime.h"
#include "device_launch_parameters.h"

void mandelbrotGPU(char*);
__global__ void calc(char* image_buffer);
void draw_mandelbrot_gpu();
