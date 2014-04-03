#include "Application.h"
#include <math.h>


void Application::OnRender() {

    // Clear everything

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw some rectangles for the outside level

    level.OnRender(renderer, &camera);

    // Render all entities

    for (int i=0;i<Entity::entities.size();i++) {
        Entity::entities[i]->OnRender(renderer, &camera);
    }

    // Render the player hud

    mainhud.OnRender(renderer, &camera,
                     Player::player->x,
                     Player::player->y,
                     astate.targetx, astate.targety,
                     Player::player->hit_pts);

    SDL_RenderPresent(renderer);
}
