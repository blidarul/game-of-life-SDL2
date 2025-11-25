#include <iostream>
#include <SDL2/SDL.h>
#include <fstream>

std::ifstream intrare("seed.txt");

const int WIDTH = 1600, HEIGHT = 900;
const int SCALE = 10;
const int W = WIDTH / SCALE, H = HEIGHT / SCALE;

int checkNeighbours(bool vector[H][W], int i, int j)
{
    int nr = 0;
    if(i > 0)
        if(vector[i-1][j])
            {nr++;}
    if(j > 0)
        if(vector[i][j-1])
            {nr++;}
    if(i < H)
        if(vector[i+1][j])
            {nr++;}
    if(j < W)
        if(vector[i][j+1])
            {nr++;}
    if(i > 0 && j > 0)
        if(vector[i-1][j-1])
            {nr++;}
    if(i > 0 && j < W)
        if(vector[i-1][j+1])
            {nr++;}
    if(i < H && j > 0)
        if(vector[i+1][j-1])
            {nr++;}
    if(i < H && j < W)
        if(vector[i+1][j+1])
            {nr++;}
    
    return nr;
}

bool isAlive(bool viata, int nr)
{
    bool alive = viata;
    
    if(!alive)
    {
        if(nr == 3)
            alive = 1;
    }
    else
    {
        if(nr < 2 || nr > 3)
            alive = 0;
    }
    return alive;
}

int main(int argc, char *argv[])
{
    //initializare
    SDL_Init(SDL_INIT_EVERYTHING);

    bool seed[H][W], buffer[H][W], buffer1[H][W];

    for(int i = 0; i <= H; i++)
        for(int j = 0; j <= W; j++)
        {
            intrare >> seed[i][j];
            if(seed[i][j] > 1)
                seed[i][j] = 1;
        }
    
    for(int i = 0; i <= H; i++)
        for(int j = 0; j <= W; j++)
            buffer[i][j] = isAlive(seed[i][j], checkNeighbours(seed,i,j));
    
    //creare fereastra
    SDL_Window *window = SDL_CreateWindow("game of life?", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH , HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    
    //verificare eroare
    if(NULL == window)
    {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return 1;
    }

    //creare renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window , -1, 0);
    SDL_RenderSetScale(renderer, SCALE, SCALE);

    //background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Event event;
    int t = 1;
    while(t <= 100000000)
    {
        if(SDL_PollEvent(&event))
        {
            if(SDL_QUIT == event.type)
            {
                break;
            }
        }
        for(int i = 0; i <= H; i++)
        {
            for(int j = 0; j <= W; j++)
            {
                buffer1[i][j] = isAlive(buffer[i][j], checkNeighbours(buffer,i,j));
                if(buffer[i][j] == 1)
                {
                    if(i % 2 == j % 2)
                        SDL_SetRenderDrawColor(renderer, 230, 230, 250, 255);
                    else
                        SDL_SetRenderDrawColor(renderer, 230, 230, 250, 255);
                    SDL_RenderDrawPoint(renderer, j, i);
                }
            }
        }
        for(int i = 0; i <= H; i++)
        {
            for(int j = 0; j <= W; j++)
            {
                buffer[i][j] = buffer1[i][j];
            }
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        t++;
    }

    while(true)
    {
        if(SDL_PollEvent(&event))
        {
            if(SDL_QUIT == event.type)
            {
                break;
            }
        }
    }

    SDL_DestroyWindow (window);
    SDL_Quit();
    intrare.close();
    return EXIT_SUCCESS;
}