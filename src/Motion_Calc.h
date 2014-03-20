#pragma once

#include <cfloat>
#include "Entity.h"
class Entity;

class Motion_Calc {
 public:
    double x, y;            // Position of Entity (CoM)
    double xforce, yforce;
    double xvel, yvel;      // Velocity
    double width, height;      // Size of Entity
    double mass;
    Motion_Calc();

    void Calc_Motion(Entity* this_ent, int ent_type,int dt,bool this_a_player);
};
