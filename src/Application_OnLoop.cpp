#include "Application.h"

void Application::OnLoop() {

    Level::p_level->world.Step((double) dt / 1000.0, 6, 2);

    for (int i=0;i<entities.size();i++) {
        entities[i]->update(graphics);
    }
    for (int i=0;i<Project::projects.size();i++) {
        Project::projects[i]->Calculate_Motion(dt);
        // if (Project::projects[i] != NULL) {
        //     Project::projects.erase(Project::projects.begin());
        //     printf("destroyed!!\n");
        // }
    }
   //if (haptic != NULL && SDL_HapticRumblePlay( haptic, 0.5, 1000 ) != 0){
        //    Logger::log("RumblePlay Fail: " + std::string(SDL_GetError()));
        //}

    return;
}
