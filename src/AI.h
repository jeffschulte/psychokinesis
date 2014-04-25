#pragma once

#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include "Entity.h"
#include "Player.h"


class AI : public InputComponent {
 public:
    double xrun;
    double yrun;
    AI(CopyPhysicsComponent* phys);
    void Calculate_Action(double x,double y);

    virtual void update(Entity& ent);

 private:
    CopyPhysicsComponent* entPhys;
};
