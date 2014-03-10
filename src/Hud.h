#pragma once

#include <SDL.h>
#include "Entity.h"

// Keeps track of all the pieces that need to be on the hud

class Hud {

    public:

        void OnRender(SDL_Renderer* renderer,
            Entity player, double targetx, double targety);
};
