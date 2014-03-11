#pragma once

#include "Entity.h"


class Player: public Entity {

  public:
    void calcMotion(int screenw, int screenh, double xcont);
};