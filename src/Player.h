#pragma once

#include "Entity.h"

class Player: public Entity {

 public:
    static Entity* player;

    Player();
    static Entity* Create(SDL_Renderer* renderer,
                          double x, double y);
};
