#pragma once

#include <SDL.h>
#include "Entity.h"
#include "Camera.h"

// Keeps track of all the pieces that need to be on the hud

class Hud {

    public:

    void OnRender(SDL_Renderer* renderer, Camera* camera,
                  double player_x, double player_y,
                  double targetx, double targety);
};
