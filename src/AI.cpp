#include "AI.h"


AI::AI(CopyPhysicsComponent* phys) : entPhys(phys), xrun(0) {}

void AI::Calculate_Action(double x, double y) {
    double dx = Player::player->x - x;
    double dy = Player::player->y - y;
    xrun = (dx > 0) ? .4 : -.4;
    yrun = (dy > 0) ? .4 : -.4;
}

void AI::update(Entity& ent) {

    Calculate_Action(ent.x, ent.y);

    if (ent.dead) {
        return;
    }

    if (fabs(Player::player->x - ent.x)
        < 1.2*(ent.width/2.0 + Player::player->width/2.0)
        && fabs(Player::player->y - ent.y) < ent.height) {
        if (Player::player->swing_right
            && (Player::player->x - ent.x) < 0.0) {
            //animation_object->hit_face_l = true;
            ent.hit_pts -= 50;
        }
        else if (Player::player->swing_left
                 && (Player::player->x - ent.x) > 0.0) {
            //animation_object->hit_face_r = true;
            ent.hit_pts -= 50;
        }
    }

    entPhys->Walk(xrun * 100, ent);
}
