#include "Application.h"


void Application::OnLoop() {

    if(astate.pushing) {

        player.yvel -= 2 * 9.8 * astate.targety * dt / 1000.0;
        player.xvel -= 2 * 9.8 * astate.targetx * dt / 1000.0;

        for (int i=0;i<Entity::entities.size();i++) {
            if(Entity::entities[i]->collideline(player.x, player.y,
                                              astate.targetx, astate.targety)) {
                Entity::entities[i]->xvel += 2 * 9.8 * astate.targetx * dt / 1000.0;
                Entity::entities[i]->yvel += 2 * 9.8 * astate.targety * dt / 1000.0;
            }
        }
        //if (haptic != NULL && SDL_HapticRumblePlay( haptic, 0.5, 1000 ) != 0) {
        //    Logger::log("RumblePlay Fail: " + std::string(SDL_GetError()));
        //}
    }

    player.calcMotion(&astate, level, dt);
    camera.x = player.x;
    //camera.y = player.y;
    camera.zoom = player.y > 22 ? 10 : -fabs(player.y) + 32;


    // TODO: The code below also needs to be generalized
    for (int i=0; i < Entity::entities.size(); i++) {

        Entity* current = Entity::entities[i];

        current->yvel -= 9.8 * dt / 1000.0;
        current->y += current->yvel * dt / 1000.0;
        current->x += current->xvel * dt / 1000.0;

        if(current->y > 25 - current->height / 2) {
            current->y = 25 - current->height / 2;
            current->yvel *= -0.8;

            current->xvel -= 0.01 * current->xvel;
        }
        if(current->x < current->width / 2) {
            current->x = current->width / 2;
            current->xvel *= -.8;
        }
        if(current->x > 25 - current->width / 2) {
            current->x = 25 - current->width / 2;
            current->xvel *= -.8;
        }
        if(current->y < current->height / 2) {
            current->y = current->height / 2;
            current->yvel *= -.8;
        }
    }
}
