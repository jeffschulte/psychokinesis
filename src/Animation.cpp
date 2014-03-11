#include "Entity.h"

int FrameRate = 1000; //Milliseconds
int MaxFrames = 0;
bool Oscillate = false;

SDL_Rect get_frame_to_render(int current_frame, int old_frame_time) {
    if(SDL_GetTicks() < old_frame_time ){
        printf("Error: oldtime is greater than current time\n");
        exit(1);
    }
    else if(SDL_GetTicks() - old_frame_time < FrameRate ){
        SDL_Rect rect = {600,current_frame*200,500,500};//xpos,ypos,width,hieght
        return rect;
    }
    else {
        SDL_Rect rect = {600,(current_frame+1)*200,500,500};
        return rect;
    }
}
