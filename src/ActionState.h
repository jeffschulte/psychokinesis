#pragma once

#include <stdio.h>
#include <Box2D/Box2D.h>
#include "Entity.h"
#include "Animation.h"

class ActionState;

class PushCallback : public b2RayCastCallback {

 public:
    virtual float32 ReportFixture(b2Fixture* fixture, const b2Vec2 & point,
                                  const b2Vec2 & normal, float32 fraction);
    PushCallback(ActionState* state);

 private:
    ActionState* astate;

};


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
    PushCallback pushcall;
};
