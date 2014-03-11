#include "Level.h"


void Level::OnRender(SDL_Renderer* renderer) {

    // For now, we'll just draw a series of lines between the points

    SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255);

    for(int i = 0; i < pointsx.size()-1; i++) {
        SDL_RenderDrawLine(renderer, pointsx[i], pointsy[i],
                           pointsx[i+1], pointsy[i+1]);
    }
}