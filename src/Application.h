#pragma once

#include <SDL.h>
#include <string>
#include "Entity.h"
#include "Hud.h"
#include "Logger.h"
#include "Player.h"
#include "Level.h"
#include "Camera.h"


class Application {
 private:
    bool Running;

    int render_rate; //milliseconds

    SDL_Renderer* renderer;
    SDL_Haptic *haptic;
    int effect_id;
    SDL_Joystick *joystick;

    int screenw, screenh;

    double xcont;
    bool pushing;

    double targetx, targety;

    Player player;
    Level level;
    Camera camera;

    Hud mainhud;

    int oldtime, dt, frametime;

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
