#pragma once

#include <stdio.h>
#include "Entity.h"
#include "Animation.h"

class ActionState : public InputComponent {

 public:
    double xcont;
    bool pushing;

    double targetx, targety;

    ActionState(Animation* anim, CopyPhysicsComponent* phys);
    virtual void update(Entity& ent);

 private:

    Animation* playerAnim;
    CopyPhysicsComponent* playerPhys;
};
