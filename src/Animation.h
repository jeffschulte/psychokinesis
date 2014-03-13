#pragma once

#include <SDL.h>
#include <String>

class Animation {
 public:
    int anim_frame_rate;
    int MaxFrames;
    int Oscillate;

    Animation();
    SDL_Texture* Animation_Load_Texture(const char* File, SDL_Renderer* renderer);
    SDL_Rect Get_Frame_to_Render(int* current_frame, int* last_frame_time);
};
