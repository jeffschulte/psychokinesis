#include "Application.h"


void Application::OnLoop() {

    if(pushing) {

        player.yvel -= 2 * 9.8 * targety * dt / 1000.0;
        player.xvel -= 2 * 9.8 * targetx * dt / 1000.0;

        for (int i=0;i<Entity::things.size();i++) {
            if(Entity::things[i]->collideline(player.x, player.y, targetx, targety)) {
                Entity::things[i]->xvel += 2 * 9.8 * targetx * dt / 1000.0;
                Entity::things[i]->yvel += 2 * 9.8 * targety * dt / 1000.0;
            }
        }
        //if (haptic != NULL && SDL_HapticRumblePlay( haptic, 0.5, 1000 ) != 0) {
        //    Logger::log("RumblePlay Fail: " + std::string(SDL_GetError()));
        //}
    }

    player.calcMotion(screenw, screenh, xcont, level, dt);

    // TODO: The code below also needs to be generalized
    for (int i=0;i<Entity::things.size();i++) {
        Entity::things[i]->yvel -= 9.8 * dt / 1000.0;
        Entity::things[i]->y += Entity::things[i]->yvel * dt / 1000.0;
        Entity::things[i]->x += Entity::things[i]->xvel * dt / 1000.0;

        if(Entity::things[i]->y > 25 - Entity::things[i]->height / 2) {
            Entity::things[i]->y = 25 - Entity::things[i]->height / 2;
            Entity::things[i]->yvel *= -0.8;

            Entity::things[i]->xvel -= 0.01 * Entity::things[i]->xvel;
        }
        if(Entity::things[i]->x < Entity::things[i]->width / 2) {
            Entity::things[i]->x = Entity::things[i]->width / 2;
            Entity::things[i]->xvel *= -.8;
        }
        if(Entity::things[i]->x > 25 - Entity::things[i]->width / 2) {
            Entity::things[i]->x = 25 - Entity::things[i]->width / 2;
            Entity::things[i]->xvel *= -.8;
        }
        if(Entity::things[i]->y < Entity::things[i]->height / 2) {
            Entity::things[i]->y = Entity::things[i]->height / 2;
            Entity::things[i]->yvel *= -.8;
        }
    }
}
