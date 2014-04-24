#pragma once

#include <SDL.h>
#include "Camera.h"


class Graphics {

 public:
    SDL_Renderer* renderer;
    Camera* camera;

};
