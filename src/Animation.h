#pragma once

#include <SDL.h>
#include <string>

class Animation {
 public:
    int anim_frame_rate;
    int MaxFrames;
    int Oscillate;
    int last_frame_time;
    int current_frame;

    int current_state;
    enum states {ON_GROUND,IN_AIR,CLOSE_GROUND};
    int mini_anim_frame;
    enum frames {STAND = 0, F_IN_AIR = 1, HIT_GROUND = 5, GET_UP =8};

    Animation();
    SDL_Texture* Animation_Load_Texture(const char* File, SDL_Renderer* renderer);
    SDL_Rect Get_Frame_to_Render(double y, double yvel, double height);
};
