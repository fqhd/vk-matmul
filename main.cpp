#include "MatrixMultiplier.hpp"
#include <chrono>
#include <iostream>

constexpr int WIDTH = 2048;

int main()
{
    float *data = new float[WIDTH * WIDTH * 3];
    for (int i = 0; i < WIDTH * WIDTH * 3; i++)
    {
        data[i] = i;
    }

    MatrixMultiplier multiplier(WIDTH, WIDTH);

    multiplier.UploadData(data);

    auto start = std::chrono::high_resolution_clock::now();
    
    for(int i = 0; i < 1000; i++) {
        multiplier.Run();
    }

    std::chrono::duration<double> dur = std::chrono::high_resolution_clock::now() - start;
    std::cout << dur.count() << " seconds" << std::endl;

    multiplier.ReadData(data + WIDTH * WIDTH * 2);

    std::cout << data[WIDTH * WIDTH * 3 - 10] << std::endl;
}