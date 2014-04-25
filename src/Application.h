#pragma once

#include <SDL.h>
#include <string>
#include <vector>
#include "Entity.h"
#include "Projectile.h"
#include "Hud.h"
#include "Logger.h"
#include "Level.h"
#include "Camera.h"
#include "ActionState.h"
#include "Player.h"
#include "Contact_Listener.h"
#include "Graphics.h"
#include "AI.h"

class Application {
 private:
    bool Running;

    ContactListener contactListen;

    int render_rate; //milliseconds

    SDL_Haptic *haptic;
    int effect_id;
    SDL_Joystick *joystick;


    int screenw, screenh;

    Level level;

    ActionState* astate;

    Graphics graphics;

    Hud mainhud;

    int oldtime, dt, frametime;

    std::vector<Entity*> entities;

 public:
    Application();
    int OnExecute();

 public:
    bool OnInit();
    void OnEvent(SDL_Event* Event);
    void OnLoop();
    void OnRender();
    void OnCleanup();

    Entity* Create(Graphics& graphics,
                       Entity::EntType type, double x, double y);
};
