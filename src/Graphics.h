#pragma once

#include <SDL.h>

class Camera;

class Graphics {

 public:
    SDL_Renderer* renderer;
    Camera* camera;

};
