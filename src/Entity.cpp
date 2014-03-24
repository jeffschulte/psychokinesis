#include "Entity.h"


std::vector<Entity*> Entity::entities;

Entity::Entity() {
    texture = NULL;
    animation_object = new Animation();
    this_a_player = false;
    hit_pts = 0;
    dead = false;
}

SDL_Texture* Entity::LoadTexture(const char* File, SDL_Renderer* renderer) {

    texture = animation_object->Animation_Load_Texture(File,renderer);
    return texture;
}


void Entity::OnRender(SDL_Renderer* renderer, Camera* camera) {

    Rect rect5 = {x - width / 2, y + height / 2, width, height};
    if (texture != NULL) {
        SDL_Rect rect =
            animation_object->Get_Frame_to_Render(x, y, xvel, yvel,
                                                  height,
                                                  int(ent_type), dead);
        camera->RenderCopyEx(renderer, texture, &rect, &rect5,
                             angle, NULL, SDL_FLIP_NONE);
    }
    else {
        SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
        camera->RenderFillRect(renderer, &rect5);
    }
}


// Method to check if the rectangle collides with a given line segemnt

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


    if (this_a_player) {
        if(ActionState::p_astate->pushing) {
            body->ApplyForce(b2Vec2(-targetx * 2 * 9.8 * 10,
                                    -targety * 2 * 9.8 * 10),
                             body->GetWorldCenter(), true);
        }

        if(fabs(xvel) < 15) {
            body->ApplyForce(b2Vec2(ActionState::p_astate->xcont * 100, 0),
                                       body->GetWorldCenter(), true);
        }

        Camera::camera->x = x;
        Camera::camera->zoom = y > 22 ? 10 : -fabs(y) + 32;
    }
    else {
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
