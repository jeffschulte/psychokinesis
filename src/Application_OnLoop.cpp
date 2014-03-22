#include "Application.h"


void Application::OnLoop() {
    for (int i=0;i<Entity::entities.size();i++) {
        Entity::entities[i]->Calculate_Motion(dt);
    }
   
    //if (haptic != NULL && SDL_HapticRumblePlay( haptic, 0.5, 1000 ) != 0){
        //    Logger::log("RumblePlay Fail: " + std::string(SDL_GetError()));
        //}
    return;
}
