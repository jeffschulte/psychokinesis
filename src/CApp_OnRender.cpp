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

    SDL_Rect rect = {0, 0, rectwidth, screenh};
    SDL_RenderFillRect(renderer, &rect);

    SDL_Rect rect2 = {0, 0, screenw, rectwidth};
    SDL_RenderFillRect(renderer, &rect2);

    SDL_Rect rect3 = {screenw-rectwidth, 0, rectwidth, screenh};
    SDL_RenderFillRect(renderer, &rect3);

    SDL_Rect rect4 = {0, screenh-rectwidth, screenw, rectwidth};
    SDL_RenderFillRect(renderer, &rect4);

    // Render the player

    player.OnRender(renderer);


    // Targeting line for push direction

    double mag = sqrt(targetx*targetx + targety*targety);
    if(mag > .2) {
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 128);
        SDL_RenderDrawLine(renderer, player.x + 30 * targetx / mag,
                            player.y + 30 * targety / mag, 
                            player.x + 30 * targetx / mag + 100 * targetx, 
                            player.y + 30 * targety / mag + 100 * targety);
    }

    SDL_RenderPresent(renderer);
}

//==============================================================================
