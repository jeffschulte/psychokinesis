#include "Application.h"
#include <math.h>


void Application::OnRender() {

    // Clear everything

    SDL_SetRenderDrawColor(graphics.renderer, 0, 0, 0, 255);
    SDL_RenderClear(graphics.renderer);

    // Draw some rectangles for the outside level

    level.OnRender(graphics.renderer, graphics.camera);

    // Render all entities

    for (int i=0;i<entities.size();i++) {
        entities[i]->update(graphics);
    }
    for (int i=0;i<Project::projects.size();i++) {
        Project::projects[i]->OnRender(graphics.renderer, graphics.camera);
    }

    // Render the player hud

    mainhud.OnRender(graphics.renderer, graphics.camera,
                     Player::player->x,
                     Player::player->y,
                     astate.targetx, astate.targety,
                     Player::player->hit_pts);

    SDL_RenderPresent(graphics.renderer);
}
