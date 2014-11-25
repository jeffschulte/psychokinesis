#include "Application.h"


void Application::OnRender() {

    Level::p_level->world.Step((double) dt / 1000.0, 6, 2);

    // Clear everything

    SDL_SetRenderDrawColor(graphics.renderer, 0, 0, 0, 255);
    SDL_RenderClear(graphics.renderer);

    // Draw some rectangles for the outside level

    level.OnRender(graphics.renderer, graphics.camera);

    // Update all entities

    for (int i=0;i<entities.size();i++) {

        entities[i]->update(graphics);

        /// \todo Again, this is messy

        if(entities[i]->removed == true) {
            delete entities[i];
            entities.erase(entities.begin()+i);
        }
    }


    // Render the player hud

    mainhud.OnRender(graphics.renderer, graphics.camera,
                     Player::player->x,
                     Player::player->y,
                     astate->targetx, astate->targety,
                     Player::player->hit_pts);

    SDL_RenderPresent(graphics.renderer);
}
