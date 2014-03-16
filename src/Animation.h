#pragma once

#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include "Logger.h"
#include "Entity.h"

class Animation {
 public:
    int anim_frame_rate;
    int MaxFrames;
    int Oscillate;
    int last_frame_time;
    int current_frame;

    int current_state;
    enum states {ON_GROUND,IN_AIR,HITTING_GROUND};
    enum player_states {P_STAND=0, PUSH_R=1, PUSH_L=2, PUSH_U=3, PUSH_D=4,
                        PUSH_R_F_STAND=5, STAND_F_PUSH_R=8, PUSH_L_F_STAND=11,
                        STAND_F_PUSH_L=14, PUSH_U_F_STAND=17, STAND_F_PUSH_U=20,
                        PUSH_D_F_STAND=23, STAND_F_PUSH_D=26, RUN_R=29, RUN_L=33,
                        RUN_R_F_STAND=37, STAND_F_RUN_R=40, RUN_L_F_STAND=43,
                        STAND_F_RUN_L=46, IN_AIR_L=49, IN_AIR_R=50, HGH_R=51,
                        HGH_L=54, HGS_R=57, HGS_L=61, WALL_HUG_L=65,
                        WALL_HUG_R=66};

    int mini_anim_frame;
    enum frames {STAND = 0, F_IN_AIR = 1, HIT_GROUND = 5, GET_UP =8};

    Animation();
    SDL_Texture* Animation_Load_Texture(const char* File, SDL_Renderer* renderer);
    SDL_Rect Get_Frame_to_Render(double y, double yvel, double height,
                                 int ent_type);
};
