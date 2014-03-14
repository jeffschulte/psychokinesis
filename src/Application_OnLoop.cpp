#include "Application.h"


void Application::OnLoop() {

    if(astate.pushing) {

        player.yvel -= 2 * 9.8 * astate.targety * dt / 1000.0;
        player.xvel -= 2 * 9.8 * astate.targetx * dt / 1000.0;

        for (int i=0;i<Entity::things.size();i++) {
            if(Entity::things[i]->collideline(player.x, player.y,
                                              astate.targetx, astate.targety)) {
                Entity::things[i]->xvel += 2 * 9.8 * astate.targetx * dt / 1000.0;
                Entity::things[i]->yvel += 2 * 9.8 * astate.targety * dt / 1000.0;
            }
        }
        //if (haptic != NULL && SDL_HapticRumblePlay( haptic, 0.5, 1000 ) != 0) {
        //    Logger::log("RumblePlay Fail: " + std::string(SDL_GetError()));
        //}
    }

    player.calcMotion(screenw, screenh, astate.xcont, level, dt);
    camera.x = player.x;
    camera.y = player.y;

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
