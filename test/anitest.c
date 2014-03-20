#include <SDL.h>


// This is a test file for interpolating between animation keyframes
//
// clang anitest.c `sdl2-config --cflags --libs` && ./a.out


double interp(double x1, double x2, int dt) {

    return ((x2-x1) * (double)(dt)) / 1000.0 + x1;
}

int main(int argc, char* argv[]) {

    // For now we specify coordinates as:

    // Torso top, torso bottom, right elbow, right hand, left elbow,
    // left hand, right knee, right foot, left knee, left foot

    const double frame1x[] = { 30.42, 27.62, 38.81, 48.60, 23.08,
                               24.13, 38.81, 27.97, 34.62, 30.07 };
    const double frame1y[] = { 1021.33, 1005.24, 1010.84, 1014.34, 1013.29,
                               1005.24, 992.31, 987.41, 989.86, 984.62 };

    const double frame2x[] = { 31.12, 27.62, 34.27, 44.76, 19.23,
                               32.52, 38.81, 30.42, 26.57, 15.73 };
    const double frame2y[] = { 1019.93, 1001.05, 1004.20, 1007.69, 1013.29,
                               1006.29, 994.06, 984.97, 989.51, 987.41 };

    double intx[10], inty[10];


    SDL_Renderer *renderer;

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return -1;
    }

    SDL_Window *screen = SDL_CreateWindow("AnimationTest",
                          SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED,
                          640, 480,
                          SDL_WINDOW_OPENGL);
    if(screen == NULL) {
        printf("SDL_CreateWindow failure\n");
        return -1;
    }

    if((renderer = SDL_CreateRenderer(screen, -1, 0)) == NULL) {
        printf("SDL_CreateRenderer failure\n");
        return -1;
    }

    int Running = 1;

    int oldtime = SDL_GetTicks();

    SDL_Event Event;

    while(Running) {

        while(SDL_PollEvent(&Event)) {
            if(Event.type == SDL_QUIT) {
                Running = 0;
            }
        }

        int dt = (SDL_GetTicks() - oldtime) % 1000;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);


        // Interpolate all points

        int i;
        for(i = 0; i < 10; i++) {
            intx[i] = interp(frame1x[i], frame2x[i], dt) * 640.0 / 60.0;
            inty[i] = (interp(frame1y[i], frame2y[i], dt) - 983.0) * 480.0 / 67.0 * -1 + 480;
        }

        //printf("%g; %g, %g\n", interp(frame1x[0], frame2x[0], dt), frame1x[0], frame2x[0]);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);


        SDL_RenderDrawLine(renderer, intx[0], inty[0], intx[1], inty[1]); // Torso
        SDL_RenderDrawLine(renderer, intx[0], inty[0], intx[2], inty[2]); // UArmR
        SDL_RenderDrawLine(renderer, intx[2], inty[2], intx[3], inty[3]); // LArmR
        SDL_RenderDrawLine(renderer, intx[0], inty[0], intx[4], inty[4]); // UArmL
        SDL_RenderDrawLine(renderer, intx[4], inty[4], intx[5], inty[5]); // LArmL
        SDL_RenderDrawLine(renderer, intx[1], inty[1], intx[6], inty[6]); // ULegR
        SDL_RenderDrawLine(renderer, intx[6], inty[6], intx[7], inty[7]); // LLegR
        SDL_RenderDrawLine(renderer, intx[1], inty[1], intx[8], inty[8]); // ULegL
        SDL_RenderDrawLine(renderer, intx[8], inty[8], intx[9], inty[9]); // LLegL


        SDL_RenderPresent(renderer);

        SDL_Delay(10);
    }
}
