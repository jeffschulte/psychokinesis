#include "Entity.h"


std::vector<Entity*> Entity::entities;

Entity::Entity() {
    texture = NULL;
    animation_object = new Animation();
    motion_object = new Motion_Calc();
    this_a_player = false;
    hit_pts = 0;
    dead = false;
}

SDL_Texture* Entity::LoadTexture(const char* File, SDL_Renderer* renderer) {

    texture = animation_object->Animation_Load_Texture(File,renderer);
    return texture;
}


void Entity::OnRender(SDL_Renderer* renderer, Camera* camera) {
    double x = motion_object->x;
    double y = motion_object->y;
    double width = motion_object->width;
    double height = motion_object->height;
    Rect rect5 = {x - width / 2, y + height / 2, width, height};
    if (texture != NULL) {
        SDL_Rect rect =
            animation_object->Get_Frame_to_Render(motion_object->x,
                                                  motion_object->y,
                                                  motion_object->xvel,
                                                  motion_object->yvel,
                                                  motion_object->height,
                                                  int(ent_type),dead);
        camera->RenderCopy(renderer, texture, &rect, &rect5);
    }
    else {
        SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
        camera->RenderFillRect(renderer, &rect5);
    }
}


// Method to check if the rectangle collides with a given line segemnt

void Entity::Calculate_Motion(int dt) {
    motion_object->Calc_Motion(this, int(ent_type), dt, this_a_player);
    return;
}


bool Entity::collideline(double xp, double yp, double targetx, double targety) {

    double m = targety / targetx;
    double b = yp - m * xp;

    double x = motion_object->x;
    double y = motion_object->y;
    double width = motion_object->width;
    double height = motion_object->height;
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
