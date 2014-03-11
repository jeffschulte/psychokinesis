#include "Application.h"
#include <math.h>


void Application::OnRender() {

    // Clear everything

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw some rectangles for the outside level

    level.OnRender(renderer);

    block.OnRender(renderer);

    // Render the player

    player.OnRender(renderer);


    // Targeting line for push direction

    mainhud.OnRender(renderer, player, targetx, targety);

    SDL_RenderPresent(renderer);
}
