#include "Entity.h"


std::vector<Entity*> Entity::entities;

Entity::Entity() {
    texture = NULL;
    animation_object = new Animation();
    AI_object = new AI();
    this_a_player = false;
    hit_pts = 0;
    dead = false;
}

SDL_Texture* Entity::LoadTexture(const char* File, SDL_Renderer* renderer) {

    texture = animation_object->Animation_Load_Texture(File,renderer);
    return texture;
}


void Entity::OnRender(SDL_Renderer* renderer, Camera* camera) {

    Rect rect5 = {x - anim_width / 2, y + anim_height / 2, anim_width, anim_height};
    if (texture != NULL) {
        SDL_Rect rect =
            animation_object->Get_Frame_to_Render(x, y, xvel, yvel, height,
                                                  int(ent_type), dead);
        camera->RenderCopyEx(renderer, texture, &rect, &rect5,
                             angle, NULL, SDL_FLIP_NONE);
    }
    else {
        SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
        camera->RenderFillRect(renderer, &rect5);
    }
}

void Entity::Calculate_Motion(int dt) {

    double targetx = ActionState::p_astate->targetx;
    double targety = ActionState::p_astate->targety;

    b2Vec2 position = body->GetPosition();
    b2Vec2 velocity = body->GetLinearVelocity();

    x = position.x;
    y = position.y;
    angle = body->GetAngle() / -b2_pi * 180.0;
    xvel = velocity.x;
    yvel = velocity.y;

    EnvLine* closest = Level::p_level->ClosestLine(x, y);
    EnvLine* second_closest = Level::p_level->SecondClosestLine(x,y, closest);
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

    if (this->hit_pts < 0.0) {
        this->dead = true;
    }

    if (this_a_player) {
        if (!dead) {
            if (swing_right == true) {
                animation_object->anim_swing_r = true;
                swing_right = false;
            }
            if (swing_left == true) {
                animation_object->anim_swing_l = true;
                swing_left = false;
            }
            if(ActionState::p_astate->pushing) {
                body->ApplyForce(b2Vec2(-targetx * 2 * 9.8 * 3,
                                        -targety * 2 * 9.8 * 3),
                                 body->GetWorldCenter(), true);
            }
            if (closest->DistToPoint(x,y).dist_to_pt < height
                && (fabs(tan_theta_closest) < .3 || fabs(tan_theta_second_closest) < .3)) {
                if(fabs(xvel) < 15) {
                    body->ApplyForce(b2Vec2(ActionState::p_astate->xcont * 100, 0),
                                     body->GetWorldCenter(), true);
                }
                else if ( (ActionState::p_astate->xcont > 0.0 && xvel < 0.0) ||
                          (ActionState::p_astate->xcont < 0.0 && xvel > 0.0) ) {
                    body->ApplyForce(b2Vec2(ActionState::p_astate->xcont * 100, 0),
                                     body->GetWorldCenter(), true);
                }
            }
            Camera::camera->x = x;
            Camera::camera->zoom = y > 22 ? 10 : -fabs(y) + 32;
        }
    }
    else {
        if (!dead) {
            if (fabs(Player::player->x - x)
                < 1.2*(width/2.0 + Player::player->width/2.0)
                && fabs(Player::player->y - y) < height) {
                if (Player::player->swing_right
                    && (Player::player->x - x) < 0.0) {
                    animation_object->hit_face_l = true;
                    hit_pts -= 50;
                }
                else if (Player::player->swing_left
                         && (Player::player->x - x) > 0.0) {
                    animation_object->hit_face_r = true;
                    hit_pts -= 50;
                }
            }
            AI_object->Calculate_Action(x,y);
            if (closest->DistToPoint(x,y).dist_to_pt < height
                && (fabs(tan_theta_closest) < .3 || fabs(tan_theta_second_closest) < .3)) {
                if(fabs(xvel) < 15) {
                    body->ApplyForce(b2Vec2(AI_object->xrun * 100, 0),
                                     body->GetWorldCenter(), true);
                }
                else if ( (AI_object->xrun > 0.0 && xvel < 0.0) ||
                          (AI_object->xrun < 0.0 && xvel > 0.0) ) {
                    body->ApplyForce(b2Vec2(AI_object->xrun * 100, 0),
                                     body->GetWorldCenter(), true);
                }
                // if(fabs(yvel) < 15) {
                //     body->ApplyForce(b2Vec2(0,AI_object->yrun * 100),
                //                      body->GetWorldCenter(), true);
                // }
            }
        }
        if(ActionState::p_astate->pushing) {
            if(collideline(Player::player->x, Player::player->y,
                           targetx, targety)) {
                body->ApplyForce(b2Vec2(targetx * 2 * 9.8 * 10,
                                        targety * 2 * 9.8 * 10),
                                 body->GetWorldCenter(), true);
            }
        }
    }
}

// Method to check if the rectangle collides with a given line segment

bool Entity::collideline(double xp, double yp, double targetx, double targety) {

    double m = targety / targetx;
    double b = yp - m * xp;

    // Equation for the line is given in y = mx + b form
    // First check the vertical, and see if it is in bounds

    double vertcoor = m * (x - width / 2) + b;

    if(vertcoor >= y - height / 2 && vertcoor <= y + height / 2) {
        if((vertcoor > yp && targety > 0) || (vertcoor < yp && targety < 0) ) {
            return true;
        }
    }

    vertcoor = m * (x + width / 2) + b;

    if(vertcoor >= y - height / 2 && vertcoor <= y + height / 2) {
        if((vertcoor > yp && targety > 0) || (vertcoor < yp && targety < 0) ) {
            return true;
        }
    }

    // Next see if it goes through the top or bottom

    double horicoor = (y - height / 2 - b) / m;

    if(horicoor >= x - width / 2 && horicoor <= x + width / 2) {
        if((horicoor > xp && targetx > 0) || (horicoor < xp && targetx < 0) ) {
            return true;
        }
    }

    horicoor = (y + height / 2 - b) / m;

    if(horicoor >= x - width / 2 && horicoor <= x + width / 2) {
        if((horicoor > xp && targetx > 0) || (horicoor < xp && targetx < 0) ) {
            return true;
        }
    }

    // None of these, then we missed

    return false;
}
