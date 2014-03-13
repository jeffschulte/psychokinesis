#include "Animation.h"

Animation::Animation() {
    anim_frame_rate = 100; //milliseconds
    current_frame = 2;
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
    // if(block.y < block.height / 2) {
    //     block.y = block.height / 2;
    //     block.yvel *= -.8;
    // }

    if(SDL_GetTicks() - last_frame_time < anim_frame_rate){
        SDL_Rect rect = {330,-270+(current_frame)*197,300,210};//xpos,ypos,width,hieght
        return rect;
    }
    else {
        last_frame_time = SDL_GetTicks();
        current_frame += 1;
        if (current_frame > MaxFrames) {
            current_frame = 2;
        }
        if (mini_anim_frame == 0) {
            if (y > height/2 + 2) {
                current_state = IN_AIR;
            }
            else if (y <= height/2 +.01) {
                current_state = ON_GROUND;
            }
            else {
                current_state = CLOSE_GROUND;
            }
        }
        switch (current_state) {
            case ON_GROUND:
                printf("on_ground");
            case IN_AIR:
                printf("in air");
            case CLOSE_GROUND:
                printf("close ground");
                break;
        }
        SDL_Rect rect =  {600,(current_frame)*100,500,500};
        return rect;
    }
}
