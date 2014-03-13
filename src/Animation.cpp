#include "Animation.h"

Animation::Animation() {
    anim_frame_rate = 500; //milliseconds
    MaxFrames = 12;
    Oscillate = false;
}

SDL_Texture* Animation::Animation_Load_Texture(const char* File, SDL_Renderer* renderer) {
    SDL_Surface* surface = NULL;

    if((surface = SDL_LoadBMP(File)) == NULL) {
        return NULL;
    }
    //might want to use SDL_ConvertSurfaceFormat
    return SDL_CreateTextureFromSurface(renderer, surface);
}

SDL_Rect Animation::Get_Frame_to_Render(int* current_frame, int* last_frame_time) {
    if(SDL_GetTicks() - *last_frame_time < anim_frame_rate){
        SDL_Rect rect = {600,(*current_frame)*100,500,500};//xpos,ypos,width,hieght
        return rect;
    }
    else {
        *last_frame_time = SDL_GetTicks();
        *current_frame += 1;
        if (*current_frame > MaxFrames) {
            *current_frame = 2;
        }
        SDL_Rect rect =  {600,(*current_frame)*100,500,500};
        return rect;
    }
}
