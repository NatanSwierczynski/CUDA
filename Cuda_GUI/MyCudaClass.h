#pragma once
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

class MyCudaClass
{
public:
    void mandelbrotGPU(char*);
    void draw_mandelbrot_gpu();
};

