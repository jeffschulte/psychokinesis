#include "Entity.h"

Entity::Entity() {

    x = y = xvel = yvel = 0;
    old_frame_time = SDL_GetTicks();
    current_frame = 0;
    texture = NULL;
}

SDL_Texture* Entity::LoadTexture(const char* File, SDL_Renderer* renderer) {
    SDL_Texture* texture;
    texture = animation_object.Animation_Load_Texture(File,renderer);
    return texture;
}


void Entity::OnRender(SDL_Renderer* renderer, int dt) {

    SDL_Rect rect5 = {x - width / 2, y - height / 2, width, height};
    if (texture != NULL) {
        SDL_Rect rect = animation_object.Get_Frame_to_Render(current_frame,old_frame_time);
        SDL_RenderCopy(renderer, texture, &rect, &rect5);
    }
    else {
        SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
        SDL_RenderFillRect(renderer, &rect5);
    }
}


// Method to check if the rectangle collides with a given line segemnt

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
