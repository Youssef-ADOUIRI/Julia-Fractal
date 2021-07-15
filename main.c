
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>

#include <math.h>

#define width 680
#define height 580


typedef struct
{
    double x;
    double y;
} Complex;

void pause();
double Re(Complex);
double Im(Complex);
double mod(Complex);
Complex sq(Complex);
Complex toComplex(double, double);
Complex addComplx(Complex, Complex);

Complex EqJulia(Complex Z, Complex c)
{
    return addComplx(sq(Z), c);
}

void Draw(SDL_Renderer *renderer, Complex C, int range, Complex center, int size, int iteration)
{
    int i = 0;
    int k = 0;
    int j = 0;


    for (k = 0; k < width; k++)
    {
        for (j = 0; j < height; j++)
        {
             
            Complex z = toComplex((double)(Re(center) - range) + (double)k / size, (double)(Im(center) - range) + (double)j / size);

            for (i = 0; i < iteration; i++)
            {
                //Limit check
                z = EqJulia(z, C);

                if (mod(z) > 2)
                    break;
            }

            //if (i == iteration)
            /*

            int grayscale = i*255/iteration;
            SDL_SetRenderDrawColor(renderer,grayscale,grayscale,grayscale , 255);
            SDL_RenderDrawPoint(renderer, k, j); */
            int grayscale = i*255/iteration;
            if(i < iteration){
            SDL_SetRenderDrawColor(renderer,grayscale ,grayscale ,33 , 255);
            }
            else
            SDL_SetRenderDrawColor(renderer,grayscale ,grayscale  ,grayscale , 255);
            SDL_RenderDrawPoint(renderer, k, j);
            
        }
    }

}

int main(int argc, char *argv[])
{

    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_Window *screen = NULL;
    SDL_Surface *windowSurface = NULL;
    SDL_Renderer *renderer = NULL;

    screen = SDL_CreateWindow("JULIA Fractal", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    if (screen == NULL)
    {
        fprintf(stderr, "Error creating the window : %s\n", SDL_GetError());
    }
    else
    {
        renderer = SDL_CreateRenderer(screen, -1, 0);
        windowSurface = SDL_GetWindowSurface(screen);

        SDL_UpdateWindowSurface(screen);

        //set the screen
        SDL_SetRenderDrawColor(renderer, 38, 38, 38, 255); // gray background color
        SDL_RenderClear(renderer);

        //draw
        SDL_SetRenderDrawColor(renderer, 30, 200, 100, 255); // set color
        Draw(renderer, toComplex(0.285 , 0.01) , 2, toComplex(0, 0), 150, 200); //Change the C coordnates to get diffret shapes

        //Show the renderings
        SDL_RenderPresent(renderer);

        //wait
        pause();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(screen);
    SDL_Quit();

    return 0;
}

double Re(Complex m)
{
    return m.x;
}
double Im(Complex m)
{
    return m.y;
}
double mod(Complex m)
{
    return sqrt((m.x) * (m.x) + (m.y) * (m.y));
}
Complex sq(Complex m)
{ // square of complex
    Complex msq;
    msq.x = (m.x) * (m.x) - (m.y) * (m.y);
    msq.y = 2 * (m.x) * (m.y);
    return msq;
}
Complex toComplex(double a, double b)
{
    Complex m;
    m.x = a;
    m.y = b;
    return m;
}
Complex addComplx(Complex z1, Complex z2)
{
    return toComplex(z1.x + z2.x, z1.y + z2.y);
}

void pause()
{
    int isDone = 1;
    SDL_Event event;

    while (isDone)
    {
        SDL_WaitEvent(&event);
        if (event.type == SDL_QUIT)
        {
            isDone = 0;
        }
    }
}
