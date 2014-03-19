#include "Application.h"


void Application::OnLoop() {


    if(astate.pushing) {
        for (int i=0;i<Entity::entities.size();i++) {
            if (Entity::entities[i]->ent_type == Entity::PLAYER) {
                Entity::entities[i]->motion_object->yvel -=
                    2 * 9.8 * astate.targety * dt / 1000.0;
                Entity::entities[i]->motion_object->xvel -=
                    2 * 9.8 * astate.targetx * dt / 1000.0;
            }
            if(Entity::entities[i]->collideline(Entity::entities[i]->motion_object->x,
                                                Entity::entities[i]->motion_object->y,
                                              astate.targetx, astate.targety)) {
                Entity::entities[i]->motion_object->xvel += 2 * 9.8 * astate.targetx * dt / 1000.0;
                Entity::entities[i]->motion_object->yvel += 2 * 9.8 * astate.targety * dt / 1000.0;
            }
            if (Entity::entities[i]->ent_type == Entity::PLAYER) {
                Entity::entities[i]->motion_object->Calculate_Motion(dt);
                camera.x = Entity::entities[i]->motion_object->x;
                camera.zoom = Entity::entities[i]->motion_object->y > 22 ?
                    10 : -fabs(Entity::entities[i]->motion_object->y) + 32;
            }
            //if (haptic != NULL && SDL_HapticRumblePlay( haptic, 0.5, 1000 ) != 0) {
            //    Logger::log("RumblePlay Fail: " + std::string(SDL_GetError()));
            //}

            // TODO: The code below also needs to be generalized
            Entity* current = Entity::entities[i];

            current->motion_object->yvel -= 9.8 * dt / 1000.0;
            current->motion_object->y += current->motion_object->yvel * dt / 1000.0;
            current->motion_object->x += current->motion_object->xvel * dt / 1000.0;

            if(current->motion_object->y > 25 - current->motion_object->height / 2) {
                current->motion_object->y = 25 - current->motion_object->height / 2;
                current->motion_object->yvel *= -0.8;

                current->motion_object->xvel -= 0.01 * current->motion_object->xvel;
            }
            if(current->motion_object->x < current->motion_object->width / 2) {
                current->motion_object->x = current->motion_object->width / 2;
                current->motion_object->xvel *= -.8;
            }
            if(current->motion_object->x > 25 - current->motion_object->width / 2) {
                current->motion_object->x = 25 - current->motion_object->width / 2;
                current->motion_object->xvel *= -.8;
            }
            if(current->motion_object->y < current->motion_object->height / 2) {
                current->motion_object->y = current->motion_object->height / 2;
                current->motion_object->yvel *= -.8;
            }
        }
    }
}
