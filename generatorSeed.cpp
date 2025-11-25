#include <iostream>
#include <fstream>

std::ofstream iesire("seed.txt");

const int WIDTH = 1600, HEIGHT = 900;
const int SCALE = 1;
const int W = WIDTH / SCALE, H = HEIGHT / SCALE;

int main()
{
    for(int i = 0; i <= H ; i++)
    {
        for(int j = 0; j <= W; j++)
            iesire << rand() % 2 << ' ';
        iesire << '\n';
    }
    iesire.close();
    return 0;
}