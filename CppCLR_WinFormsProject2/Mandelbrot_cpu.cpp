#include "pch.h"

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <chrono>

using namespace cv;
using namespace std;
using namespace std::chrono;

//#define HEIGHT 512 // must be multiple of block_size.y
//#define WIDTH 512 // must be multiple of block_size.x
//#define MAX_ITER 10000

// To get color Mandelbrot change 'char' to 'Vec3b' and 'CV_8UC1' to 'CV_8UC3' and uncomment code with for coloring

void calc(char* image_buffer, int HEIGHT, int WIDTH, int MAX_ITER)
{
    for (int row = 0; row < HEIGHT; row++)
    {
        for (int col = 0; col < WIDTH; col++)
        {
            int idx = row * WIDTH + col;
            double x0 = ((double)col / WIDTH) * 3.5 - 2.5;
            double y0 = ((double)row / HEIGHT) * 3.5 - 1.75;
            double x = 0.0;
            double y = 0.0;
            int iter = 0;
            double xtemp;
            while ((x * x + y * y <= 4.0) && (iter < MAX_ITER))
            {
                xtemp = x * x - y * y + x0;
                y = 2.0 * x * y + y0;
                x = xtemp;
                iter++;
            }
            // White-Black
            int color = iter * 5;
            if (color >= 256) color = 0;
            image_buffer[idx] = color;

            // Color
            //Vec3b color;
            //if (iter < MAX_ITER) {
            //    color = Vec3b(iter % 64, iter % 128, iter % 256);
            //    //color = Vec3b(iter % 8 *  32, iter % 16 * 16, iter % 32 * 8);
            //}
            //else {
            //    color = Vec3b(0, 0, 0);
            //}

            image_buffer[idx] = color;
        }
    }
}

void draw_mandelbrot(int HEIGHT, int WIDTH, int MAX_ITER)
{
    char* image_data = new char[HEIGHT * WIDTH];

    // start time measurement
    auto start_time = high_resolution_clock::now();

    calc(image_data, HEIGHT, WIDTH, MAX_ITER);

    // stop time measurement
    auto stop_time = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop_time - start_time);
    //cout << "Time taken: " << duration.count() << " milliseconds" << endl;

    Mat image_output_show(HEIGHT, WIDTH, CV_8UC1, image_data);

    // show time measurement
    if (WIDTH > 199) {
        putText(image_output_show, "Time taken: " + to_string(duration.count()) + "ms", Point(10, 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 2);
    }
    imshow("Mandelbrot set CPU", image_output_show);
    waitKey(0);
    // save picture in file
    //imwrite("H" + to_string(HEIGHT) + "_W" + to_string(WIDTH) + "_I" + to_string(MAX_ITER) + ".jpg", image_output_show);
    delete[] image_data;

}

void zoom_mandelbrot(int HEIGHT, int WIDTH, int MAX_ITER, int zoom_iterations)
{
    char* image_buffer = new char[HEIGHT * WIDTH];
    double zoom_factor = 1.;
    Point2d center(WIDTH / 2, HEIGHT / 2);
    //double x0 = -0.75;
    //double y0 = 0;
    //int zoom_iterations = 10;

    // start time measurement
    auto start_time = high_resolution_clock::now();

    for (int i = 0; i < zoom_iterations; i++)
    {
        for (int row = 0; row < HEIGHT; row++)
        {
            for (int col = 0; col < WIDTH; col++)
            {
                int idx = row * WIDTH + col;
                //float x0 = ((float)col / WIDTH) * 3.5f - 2.5f;
                //float y0 = ((float)row / HEIGHT) * 3.5f - 1.75f;
                double x0 = (((double)col / WIDTH) - center.x / WIDTH) * 3.5 / zoom_factor - 1.4184;
                double y0 = (((double)row / HEIGHT) - center.y / HEIGHT) * 3.5 / zoom_factor - 0.0;
                //x0 = x0 + (((float)col / WIDTH) - 0.5) * 3.5f / zoom_factor;
                //y0 = y0 + (((float)row / HEIGHT) - 0.5) * 3.5f / zoom_factor;
                double x = 0.0;
                double y = 0.0;
                int iter = 0;
                double xtemp;
                while ((x * x + y * y <= 4.0) && (iter < MAX_ITER))
                {
                    xtemp = x * x - y * y + x0;
                    y = 2.0 * x * y + y0;
                    x = xtemp;
                    iter++;
                }
                // White-Black
                int color = iter * 5;
                if (color >= 256) color = 0;
                image_buffer[idx] = color;

                //Vec3b color;
                //if (iter < MAX_ITER) {
                //    color = Vec3b(iter % 64, iter % 128, iter % 256);
                //    //color = Vec3b(iter % 8 *  32, iter % 16 * 16, iter % 32 * 8);
                //}
                //else {
                //    color = Vec3b(0, 0, 0);
                //}

                image_buffer[idx] = color;

            }
        }
        zoom_factor *= 2;

        //// 'Animation' of the zooming process
        //Mat image_output_show(HEIGHT, WIDTH, CV_8UC1, image_buffer);

        //// stop time measurement
        //auto stop_time = high_resolution_clock::now();
        //auto duration = duration_cast<milliseconds>(stop_time - start_time);
        ////cout << "Time taken: " << duration.count() << " milliseconds" << endl;

        //// show zoom iterations
        //if (WIDTH > 199) {
        //    putText(image_output_show, "Zoom iterations: " + to_string(i+1), Point(10, 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 2);
        //}
        //// show time measurement
        //if (WIDTH > 199) {
        //    putText(image_output_show, "Time taken: " + to_string(duration.count()) + "ms", Point(10, 40), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 2);
        //}
        //imshow("Mandelbrot set CPU - zoom in", image_output_show);
        //waitKey(1000);
    }

    Mat image_output_show(HEIGHT, WIDTH, CV_8UC1, image_buffer);

    // stop time measurement
    auto stop_time = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop_time - start_time);
    //cout << "Time taken: " << duration.count() << " milliseconds" << endl;

    // show zoom iterations
    if (WIDTH > 199) {
        putText(image_output_show, "Zoom iterations: " + to_string(zoom_iterations), Point(10, 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 2);
    }
    // show time measurement
    if (WIDTH > 199) {
        putText(image_output_show, "Time taken: " + to_string(duration.count()) + "ms", Point(10, 40), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 2);
    }
    imshow("Mandelbrot set CPU - zoom in", image_output_show);

    waitKey(0);
    delete[] image_buffer;
}