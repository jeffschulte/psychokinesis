#include "Hud.h"


void Hud::OnRender(SDL_Renderer* renderer, Camera* camera,
                   Entity* player, double targetx, double targety) {

    double mag = sqrt(targetx*targetx + targety*targety);

    if(mag > .2) {
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 128);
        camera->RenderDrawLine(renderer, player->motion_object->x + 3 * targetx / mag,
                            player->motion_object->y + 3 * targety / mag,
                            player->motion_object->x + 3 * targetx / mag + 10 * targetx,
                            player->motion_object->y + 3 * targety / mag + 10 * targety);
    }
}
