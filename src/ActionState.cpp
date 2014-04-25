#include "ActionState.h"


ActionState::ActionState(Animation* anim, CopyPhysicsComponent* phys)
    : playerAnim(anim), playerPhys(phys), xcont(0),
      targetx(0), targety(0), pushing(false) {}

void ActionState::update(Entity& ent) {

    if(ent.dead) {
        return;
    }

    EnvLine* closest = Level::p_level->ClosestLine(ent.x, ent.y);
    EnvLine* second_closest =
        Level::p_level->SecondClosestLine(ent.x, ent.y, closest);
    double tan_theta_closest;
    double tan_theta_second_closest;
    if (fabs(closest->x2 - closest->x1) < DBL_EPSILON) {
        tan_theta_closest = (closest->y2 - closest->y1) / DBL_EPSILON;
    }
    else {
        tan_theta_closest = (closest->y2 - closest->y1)
            / (closest->x2 - closest->x1);
    }
    if (fabs(second_closest->x2 - second_closest->x1) < DBL_EPSILON) {
        tan_theta_second_closest =
            (second_closest->y2 - second_closest->y1) / DBL_EPSILON;
    }
    else {
        tan_theta_second_closest =
            (second_closest->y2 - second_closest->y1)
            / (second_closest->x2 - second_closest->x1);
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
    }

    if (closest->DistToPoint(ent.x,ent.y).dist_to_pt < ent.height
        && (fabs(tan_theta_closest) < .3
            || fabs(tan_theta_second_closest) < .3)) {

        if(fabs(ent.xvel) < 15) {
            playerPhys->ApplyForce(xcont * 100, 0);
        }
        else if ( (xcont > 0.0 && ent.xvel < 0.0) ||
                  (xcont < 0.0 && ent.xvel > 0.0) ) {
            playerPhys->ApplyForce(xcont * 100, 0);
        }
    }
}
