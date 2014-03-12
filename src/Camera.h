#pragma once

#include <SDL.h>

class Rect {

 public:
    double x, y, w, h;
};

class Camera {

 public:
    double x, y, zoom;
    int hscreenw, hscreenh;

    Camera();
    int RenderCopy(SDL_Renderer* renderer, SDL_Texture* texture,
                   const SDL_Rect* srcrect,
                   const Rect* dstrect);
    int RenderFillRect(SDL_Renderer* renderer,
                       const Rect* rect);
    int RenderDrawLine(SDL_Renderer* renderer,
                           double x1,
                           double y1,
                           double x2,
                           double y2);
};
