#pragma once

#include <cfloat>

#include "Entity.h"
#include "Level.h"
#include "ActionState.h"


class Player: public Entity {

  public:
    void calcMotion(ActionState* s, Level level, int dt);
    static Player Create(SDL_Renderer* renderer,double x, double y);
};
