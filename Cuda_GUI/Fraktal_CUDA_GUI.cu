#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <chrono>

using namespace cv;
using namespace std;
using namespace std::chrono;

#define HEIGHT 512 // must be multiple of block_size.y
#define WIDTH 512 // must be multiple of block_size.x
#define MAX_ITER 10000

void draw_mandelbrot_gpu();
void mandelbrotGPU(char*);
__global__ void calc(char* image_buffer);

#define cudaAssertSuccess(ans) { _cudaAssertSuccess((ans), __FILE__, __LINE__); }
inline void _cudaAssertSuccess(cudaError_t code, char* file, int line)
{
    if (code != cudaSuccess) {
        fprintf(stderr, "_cudaAssertSuccess: %s %s %d\n", cudaGetErrorString(code), file, line);
        exit(code);
    }
}

//int main(int argc, char** argv)
void draw_mandelbrot_gpu()
{
    Mat image_output(HEIGHT, WIDTH, CV_8UC1);
    char* image_data = new char[HEIGHT * WIDTH];
    memcpy(image_data, image_output.data, HEIGHT * WIDTH);

    // start time measurement
    auto start_time = high_resolution_clock::now();

    mandelbrotGPU(image_data);

    // stop time measurement
    auto stop_time = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop_time - start_time);
    //cout << "Time taken: " << duration.count() << " milliseconds" << endl;

    Mat image_output_show(HEIGHT, WIDTH, CV_8UC1, image_data);

    // show duration time
    if (WIDTH > 199) {
        putText(image_output_show, "Time taken: " + to_string(duration.count()) + "ms", Point(10, 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 2);
    }

    imshow("GPU", image_output_show);
    waitKey(0);
    delete[] image_data;

}

void mandelbrotGPU(char* image_buffer)
{
    char* d_image_buffer;
    cudaAssertSuccess(cudaMalloc(&d_image_buffer, WIDTH * HEIGHT));
    dim3 block_size(16, 16);
    dim3 grid_size(WIDTH / block_size.x, HEIGHT / block_size.y);
    calc << <grid_size, block_size >> > (d_image_buffer);
    cudaAssertSuccess(cudaPeekAtLastError());
    cudaAssertSuccess(cudaDeviceSynchronize());
    cudaAssertSuccess(cudaMemcpy(image_buffer, d_image_buffer, HEIGHT * WIDTH, cudaMemcpyDeviceToHost));
    cudaAssertSuccess(cudaFree(d_image_buffer));
}

__global__ void calc(char* image_buffer)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;  // WIDTH
    int col = blockIdx.x * blockDim.x + threadIdx.x;  // HEIGHT
    int idx = row * WIDTH + col;
    if (col >= WIDTH || row >= HEIGHT) return;

    float x0 = ((float)col / WIDTH) * 3.5f - 2.5f;
    float y0 = ((float)row / HEIGHT) * 3.5f - 1.75f;

    float x = 0.0f;
    float y = 0.0f;
    int iter = 0;
    float xtemp;
    while ((x * x + y * y <= 4.0f) && (iter < MAX_ITER))
    {
        xtemp = x * x - y * y + x0;
        y = 2.0f * x * y + y0;
        x = xtemp;
        iter++;
    }

    int color = iter * 5;
    if (color >= 256) color = 0;
    image_buffer[idx] = color;
}

int main(int argc, char** argv)
{
    draw_mandelbrot_gpu();
}

