#include "Application.h"

void Application::OnLoop() {

    Level::p_level->world.Step((double) dt / 1000.0, 6, 2);

    for (int i=0;i<Entity::entities.size();i++) {
        Entity::entities[i]->Calculate_Motion(dt);
    }
   //if (haptic != NULL && SDL_HapticRumblePlay( haptic, 0.5, 1000 ) != 0){
        //    Logger::log("RumblePlay Fail: " + std::string(SDL_GetError()));
        //}
    return;
}
