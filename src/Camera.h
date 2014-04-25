#pragma once

#include <SDL.h>
#include "Entity.h"
#include "Player.h"

class Rect {

 public:
    double x;  ///< the x location of the rectangle's upper left corner
    double y;  ///< the y location of the rectangle's upper left corner
    double w;  ///< the width of the rectangle
    double h;  ///< the height of the rectangle
};

class Camera {

 public:
    double x;      ///< X coordinate center of focus of camera in world space
    double y;      ///< Y coordinate center of focus of camera in world space
    double zoom;   ///< Zoom factor of camera

    Camera();
    int RenderCopy(SDL_Renderer* renderer, SDL_Texture* texture,
                   const SDL_Rect* srcrect,
                   const Rect* dstrect);
    int RenderCopyEx(SDL_Renderer* renderer, SDL_Texture* texture,
                     const SDL_Rect* srcrect,
                     const Rect* dstrect, const double angle,
                     const SDL_Point* center,
                     const SDL_RendererFlip flip);
    int RenderFillRect(SDL_Renderer* renderer,
                       const Rect* rect);
    int RenderDrawLine(SDL_Renderer* renderer,
                           double x1,
                           double y1,
                           double x2,
                           double y2);

 private:
    int hscreenw, hscreenh;
};

class CameraControl : public InputComponent {

 public:
    CameraControl(Camera* cam);
    virtual void update(Entity& ent);

 private:
    Camera* camera;
};
