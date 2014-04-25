#include "AI.h"


AI::AI(CopyPhysicsComponent* phys) : entPhys(phys), xrun(0) {}

void AI::Calculate_Action(double x, double y) {
    double dx = Player::player->x - x;
    double dy = Player::player->y - y;
    xrun = (dx > 0) ? .4 : -.4;
    yrun = (dy > 0) ? .4 : -.4;
}

void AI::update(Entity& ent) {

    // TODO: Undo this code duplication with player calcs

    EnvLine* closest = Level::p_level->ClosestLine(ent.x, ent.y);
    EnvLine* second_closest =
        Level::p_level->SecondClosestLine(ent.x, ent.y, closest);
    double tan_theta_closest;
    double tan_theta_second_closest;
    if (fabs(closest->x2 - closest->x1) < DBL_EPSILON) {
        tan_theta_closest = (closest->y2 - closest->y1)/DBL_EPSILON;
    }
    else {
        tan_theta_closest = (closest->y2 - closest->y1)
            /(closest->x2 - closest->x1);
    }
    if (fabs(second_closest->x2 - second_closest->x1) < DBL_EPSILON) {
        tan_theta_second_closest =
            (second_closest->y2 - second_closest->y1)/DBL_EPSILON;
    }
    else {
        tan_theta_second_closest =
            (second_closest->y2 - second_closest->y1)
            /(second_closest->x2 - second_closest->x1);
    }

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

    if (closest->DistToPoint(ent.x,ent.y).dist_to_pt < ent.height
        && (fabs(tan_theta_closest) < .3 || fabs(tan_theta_second_closest) < .3)) {
        if(fabs(ent.xvel) < 15) {
            entPhys->ApplyForce(xrun * 100, 0);
        }
        else if ( (xrun > 0.0 && ent.xvel < 0.0) ||
                  (xrun < 0.0 && ent.xvel > 0.0) ) {
            entPhys->ApplyForce(xrun * 100, 0);
        }
        // if(fabs(yvel) < 15) {
        //     body->ApplyForce(b2Vec2(0,AI_object->yrun * 100),
        //                      body->GetWorldCenter(), true);
        // }
    }

    // TODO: Figure out this coupling as well

    // if(ActionState::p_astate->pushing) {
    //     if(collideline(Player::player->x, Player::player->y,
    //                    targetx, targety)) {
    //         body->ApplyForce(b2Vec2(targetx * 2 * 9.8 * 10,
    //                                 targety * 2 * 9.8 * 10),
    //                          body->GetWorldCenter(), true);
    //     }
    // }
}

// Method to check if the rectangle collides with a given line segment

bool AI::collideline(Entity& ent, double xp, double yp,
                     double targetx, double targety) {

    double m = targety / targetx;
    double b = yp - m * xp;

    // Equation for the line is given in y = mx + b form
    // First check the vertical, and see if it is in bounds

    double vertcoor = m * (ent.x - ent.width / 2) + b;

    if(vertcoor >= ent.y - ent.height / 2 &&
       vertcoor <= ent.y + ent.height / 2) {
        if((vertcoor > yp && targety > 0) || (vertcoor < yp && targety < 0) ) {
            return true;
        }
    }

    vertcoor = m * (ent.x + ent.width / 2) + b;

    if(vertcoor >= ent.y - ent.height / 2 &&
       vertcoor <= ent.y + ent.height / 2) {
        if((vertcoor > yp && targety > 0) || (vertcoor < yp && targety < 0) ) {
            return true;
        }
    }

    // Next see if it goes through the top or bottom

    double horicoor = (ent.y - ent.height / 2 - b) / m;

    if(horicoor >= ent.x - ent.width / 2 && horicoor <= ent.x + ent.width / 2) {
        if((horicoor > xp && targetx > 0) || (horicoor < xp && targetx < 0) ) {
            return true;
        }
    }

    horicoor = (ent.y + ent.height / 2 - b) / m;

    if(horicoor >= ent.x - ent.width / 2 && horicoor <= ent.x + ent.width / 2) {
        if((horicoor > xp && targetx > 0) || (horicoor < xp && targetx < 0) ) {
            return true;
        }
    }

    // None of these, then we missed

    return false;
}
