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

    mainhud.OnRender(renderer, player, targetx, targety);

    SDL_RenderPresent(renderer);
}

//==============================================================================
