#include "Animation.h"

Animation::Animation() {
    anim_frame_rate = 50; //milliseconds
    current_frame = 0;
    last_frame_time = 0;
    MaxFrames = 12;
    Oscillate = false;

    current_state = 0;
    mini_anim_frame = 0;
    //enum frames {STAND = 0, IN_AIR = 1, HIT_GROUND = 5, GET_UP =8};

}

SDL_Texture* Animation::Animation_Load_Texture(const char* File, SDL_Renderer* renderer) {
    SDL_Surface* surface = NULL;

    if((surface = SDL_LoadBMP(File)) == NULL) {
        return NULL;
    }
    //might want to use SDL_ConvertSurfaceFormat
    return SDL_CreateTextureFromSurface(renderer, surface);
}

SDL_Rect Animation::Get_Frame_to_Render(double y, double yvel, double height) {

    if(SDL_GetTicks() - last_frame_time < anim_frame_rate){
        SDL_Rect rect = {330,-270+(current_frame)*197,300,210};//xpos,ypos,width,hieght
        return rect;
    }
    else {
        last_frame_time = SDL_GetTicks();
        if (mini_anim_frame == 0) {
            if (y <= height/2 +.01) {
                current_state = ON_GROUND;
            }
            else if (y > height/2 + 5 || yvel > 0) {
                current_state = IN_AIR;
            }
            else {
                current_state = HITTING_GROUND;
            }
        }
        switch (current_state) {
            case ON_GROUND:
                current_frame = STAND;
                break;
            case IN_AIR:
                current_frame = F_IN_AIR + mini_anim_frame;
                mini_anim_frame += 1;
                if (mini_anim_frame == 4) {
                    mini_anim_frame = 0;
                }
                break;
            case HITTING_GROUND:
                current_frame = HIT_GROUND + mini_anim_frame;
                mini_anim_frame += 1;
                if (mini_anim_frame == 7) {
                    mini_anim_frame = 0;
                }
                break;
        }
        SDL_Rect rect =  {330,-270+(current_frame)*197,300,210};
        return rect;
    }
}
