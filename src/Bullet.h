#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <Box2D/Box2D.h>
#include "Entity.h"
#include "Camera.h"

class Bullet {

 public:
    static Entity* Create(b2World* worldc, Graphics& graphics,
                          double x, double y,
                          double xvel, double yvel);
};

class StaticRenderComponent : public RenderComponent {

 public:
    virtual void update(Entity& ent, Graphics& graphics);
    StaticRenderComponent(const char* File, Graphics& graphics);

 private:
    SDL_Texture* texture;
};
