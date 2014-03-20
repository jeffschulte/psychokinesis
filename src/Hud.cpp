#include "Hud.h"


void Hud::OnRender(SDL_Renderer* renderer, Camera* camera,
                   double player_x, double player_y,
                   double targetx, double targety) {

    double mag = sqrt(targetx*targetx + targety*targety);

    if(mag > .2) {
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 128);
        camera->RenderDrawLine(renderer, player_x + 3 * targetx / mag,
                            player_y + 3 * targety / mag,
                            player_x + 3 * targetx / mag + 10 * targetx,
                            player_y + 3 * targety / mag + 10 * targety);
    }
}
