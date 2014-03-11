#pragma once

#include <SDL.h>
#include <String>
#include "Entity.h"
#include "Hud.h"
#include "Logger.h"
#include "Player.h"


class Application {
 private:
    bool Running;

    SDL_Renderer* renderer;
    SDL_Haptic *haptic;
    SDL_Joystick *joystick;

    int screenw, screenh;

    double xcont;

    double targetx, targety;

    Entity wallleft, wallright, walltop, wallbottom, block;
    Player player;

    Hud mainhud;
 public:
    Application();
    int OnExecute();

 public:
    bool OnInit();
    void OnEvent(SDL_Event* Event);
    void OnLoop();
    void OnRender();
    void OnCleanup();
};
