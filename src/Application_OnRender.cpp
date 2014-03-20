#include "Application.h"
#include <math.h>


void Application::OnRender() {

    // Clear everything

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw some rectangles for the outside level
    level.OnRender(renderer, &camera);
    for (int i=0;i<Entity::entities.size();i++) {
        Entity::entities[i]->OnRender(renderer, &camera);
        if (Entity::entities[i]->this_a_player) {
            mainhud.OnRender(renderer, &camera,
                             Entity::entities[i]->motion_object->x,
                             Entity::entities[i]->motion_object->y,
                             astate.targetx, astate.targety);
        }
    }
    // Render the player


    // Targeting line for push direction

    SDL_RenderPresent(renderer);
}
