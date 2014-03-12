#include "Application.h"
#include <math.h>


void Application::OnRender() {

    // Clear everything

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw some rectangles for the outside level

    level.OnRender(renderer, &camera);

    block.OnRender(renderer, &camera);

    // Render the player

    player.OnRender(renderer, &camera);


    // Targeting line for push direction

    mainhud.OnRender(renderer, &camera, player, targetx, targety);

    SDL_RenderPresent(renderer);
}
