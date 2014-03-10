
#include "Entity.h"

Entity::Entity() {

    x = y = xvel = yvel = 0;
}

void Entity::OnRender(SDL_Renderer* renderer) {
    
    // One for the main character

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_Rect rect5 = {x - width / 2, y - height / 2, width, height};
    SDL_RenderFillRect(renderer, &rect5);
}