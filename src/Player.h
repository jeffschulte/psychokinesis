#pragma once

#include "Entity.h"
#include "Level.h"


class Player: public Entity {

  public:
    void calcMotion(int screenw, int screenh, double xcont, Level level, int dt);
};
