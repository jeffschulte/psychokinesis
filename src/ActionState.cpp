#include "ActionState.h"


ActionState::ActionState(Animation* anim, CopyPhysicsComponent* phys)
    : xcont(0), pushing(false), targetx(0), targety(0),
      playerAnim(anim), playerPhys(phys), pushcall(this) {}

void ActionState::update(Entity& ent) {

    if(ent.dead) {
        return;
    }

    if (ent.hit_pts < 0.0) {
        ent.dead = true;
    }

    if (ent.swing_right == true) {
        playerAnim->anim_swing_r = true;
        ent.swing_right = false;
    }
    if (ent.swing_left == true) {
        playerAnim->anim_swing_l = true;
        ent.swing_left = false;
    }
    if (ent.shoot_right == true) {
        playerAnim->anim_shoot_r = true;
        ent.shoot_right = false;
    }
    if (ent.shoot_left == true) {
        playerAnim->anim_shoot_l = true;
        ent.shoot_left = false;
    }

    if(pushing) {
        playerPhys->ApplyForce(-targetx * 2 * 9.8 * 3,
                               -targety * 2 * 9.8 * 3);

        b2Vec2 p1(ent.x, ent.y);
        b2Vec2 p2 = p1 + b2Vec2(targetx, targety) * 1000;
        //Logger::log(std::to_string(p1.x) + " " + std::to_string(p1.y) + " " +
        //            std::to_string(p2.x) + " " + std::to_string(p2.y));
        Level::p_level->world.RayCast(&pushcall, p1, p2);
    }

    playerPhys->Walk(xcont * 100, ent);
}

PushCallback::PushCallback(ActionState* state) : astate(state) {}

float32 PushCallback::ReportFixture(b2Fixture* fixture, const b2Vec2 & point,
                                    const b2Vec2 & normal, float32 fraction) {

    //Logger::log("Raycast callback");

    b2Body* body = fixture->GetBody();

    if(body->GetUserData() == NULL) {
        return 1;  // Continue the ray cast
    }
    else {
        body->ApplyForce(b2Vec2(astate->targetx * 2 * 9.8 * 3,
                                astate->targety * 2 * 9.8 * 3),
                         body->GetWorldCenter(), true);

        //Logger::log("Raycast hit");

        return 1;  // Continue the cast
    }
}
