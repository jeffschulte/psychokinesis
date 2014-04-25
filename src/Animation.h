#pragma once

#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include "Logger.h"
#include "Entity.h"
#include "Graphics.h"
#include "Level.h"


struct states_struct {
    int beg_frame;
    int maframe_lim;
    int end_state;
};

class Animation : public RenderComponent {
 public:
    int anim_frame_rate;
    int MaxFrames;
    int Oscillate;
    int last_frame_time;
    int current_frame;
    int mini_anim_frame;
    int current_state;
    bool still_dead;
    bool hit_face_r;
    bool hit_face_l;
    bool anim_swing_r;
    bool anim_swing_l;
    bool anim_shoot_r;
    bool anim_shoot_l;
    enum player_states {P_STAND, PUSH_R, PUSH_L, PUSH_U, PUSH_D,
                        PUSH_R_F_STAND, STAND_F_PUSH_R, PUSH_L_F_STAND,
                        STAND_F_PUSH_L, PUSH_U_F_STAND, STAND_F_PUSH_U,
                        PUSH_D_F_STAND, STAND_F_PUSH_D, RUN_R, RUN_L,
                        RUN_R_F_STAND, STAND_F_RUN_R, RUN_L_F_STAND,
                        STAND_F_RUN_L, FREE_D, FREE_U, HG_FREE_D,
                        FREE_D_F_STAND, STAND_F_FREE_D, H_WALL_L,
                        H_WALL_R, H_WALL_L_F_STAND, STAND_F_H_WALL_L,
                        H_WALL_R_F_STAND, STAND_F_H_WALL_R, SWING_L,
                        SWING_R,HIT_FACE_F_R,HIT_FACE_F_L,DEAD,DYING,
                        SHOOT_L,SHOOT_R};

    Uint8 red, green, blue;

    SDL_Texture* texture;

    Animation(const char* File,
              SDL_Renderer* renderer);
    void update(Entity& ent, Graphics& graphics);
    SDL_Texture* Animation_Load_Texture(const char* File,
                                        SDL_Renderer* renderer);
    SDL_Rect Get_Frame_to_Render(Entity& ent);
 private:
    int get_next_state(Entity& ent, double targetx, double targety,
                       double xcont, double dist_to_ground);
    states_struct states[SHOOT_R+1];
    void initialize_states_list_values();
};
