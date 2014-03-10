
#include "Hud.h"

void Hud::OnRender(SDL_Renderer* renderer, Entity player, double targetx, double targety) {
    
    double mag = sqrt(targetx*targetx + targety*targety);

    if(mag > .2) {
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 128);
        SDL_RenderDrawLine(renderer, player.x + 30 * targetx / mag,
                            player.y + 30 * targety / mag, 
                            player.x + 30 * targetx / mag + 100 * targetx, 
                            player.y + 30 * targety / mag + 100 * targety);
    }
}