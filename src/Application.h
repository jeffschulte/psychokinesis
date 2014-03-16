#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include <string>
#include "Entity.h"
#include "Hud.h"
#include "Logger.h"
#include "Player.h"
#include "Level.h"
#include "Camera.h"
#include "ActionState.h"


class Application {
 private:
    bool Running;

    int render_rate; //milliseconds

    SDL_Renderer* renderer;
    SDL_Haptic *haptic;
    int effect_id;
    SDL_Joystick *joystick;

    Mix_Music* music;

    int screenw, screenh;

    Player player;
    Level level;
    Camera camera;
    ActionState astate;

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
