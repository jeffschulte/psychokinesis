#pragma once

#include <SDL.h>

class Camera {

 public:
    double x, y, zoom;
    int hscreenw, hscreenh;

    Camera();
    int RenderCopy(SDL_Renderer* renderer, SDL_Texture* texture,
                   const SDL_Rect* srcrect,
                   const SDL_Rect* dstrect);
    int RenderFillRect(SDL_Renderer* renderer,
                       const SDL_Rect* rect);
    int RenderDrawLine(SDL_Renderer* renderer,
                           int x1,
                           int y1,
                           int x2,
                           int y2);
};
