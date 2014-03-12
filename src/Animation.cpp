#include "Animation.h"

Animation::Animation() {
    object_frame_rate = 1000;
    MaxFrames = 10;
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

SDL_Rect Animation::Get_Frame_to_Render(int current_frame, int old_frame_time) {
    if(SDL_GetTicks() < old_frame_time ){
        printf("Error: oldtime is greater than current time\n");
        exit(1);
    }
    else if(SDL_GetTicks() - old_frame_time < object_frame_rate){
        SDL_Rect rect = {600,current_frame*200,500,500};//xpos,ypos,width,hieght
        return rect;
    }
    else {
        SDL_Rect rect = {600,(current_frame+1)*200,500,500};
        return rect;
    }
}
