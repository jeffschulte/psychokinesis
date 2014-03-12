#pragma once

#include <SDL.h>
#include <String>
#include "Entity.h"
#include "Hud.h"
#include "Logger.h"
#include "Player.h"
#include "Level.h"


class Application {
 private:
    bool Running;

    int oldtime;
    int render_rate; //milliseconds
    int dt;
    enum frames {STAND = 0, RUN_RIGHT = 10, RUN_LEFT = 20};

    SDL_Renderer* renderer;
    SDL_Haptic *haptic;
    int effect_id;
    SDL_Joystick *joystick;

    int screenw, screenh;

    double xcont;
    bool pushing;

    double targetx, targety;

    Entity block;
    Player player;
    Level level;

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
