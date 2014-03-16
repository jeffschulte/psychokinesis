#pragma once

#include <cfloat>

#include "Entity.h"
#include "Level.h"
#include "ActionState.h"


class Player: public Entity {

  public:
    void calcMotion(ActionState* s, Level level, int dt);
    void Create(SDL_Renderer* renderer,double xp, double yp);
};
