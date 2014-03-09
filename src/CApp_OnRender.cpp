//==============================================================================
#include "CApp.h"
#include <math.h>

//==============================================================================
void CApp::OnRender() {

    // Clear everything

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw some rectangles for the outside level

    SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255);
    int rectwidth = 50;

    SDL_Rect rect = {0, 0, rectwidth, 480};
    SDL_RenderFillRect(renderer, &rect);

    SDL_Rect rect2 = {0, 0, 640, rectwidth};
    SDL_RenderFillRect(renderer, &rect2);

    SDL_Rect rect3 = {640-rectwidth, 0, rectwidth, 480};
    SDL_RenderFillRect(renderer, &rect3);

    SDL_Rect rect4 = {0, 480-rectwidth, 640, rectwidth};
    SDL_RenderFillRect(renderer, &rect4);


    // One for the main character

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_Rect rect5 = {Mainlocx, Mainlocy, 12, 25};
    SDL_RenderFillRect(renderer, &rect5);


    // Targeting line for push direction

    double mag = sqrt(targetx*targetx + targety*targety);
    if(mag > .2) {
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 128);
        SDL_RenderDrawLine(renderer, Mainlocx + 6 + 30 * targetx / mag,
                            Mainlocy + 12 + 30 * targety / mag, 
                            Mainlocx + 30 * targetx / mag + 100 * targetx, 
                            Mainlocy + 12 + 6 + 30 * targety / mag + 100 * targety);
    }

    SDL_RenderPresent(renderer);
}

//==============================================================================
