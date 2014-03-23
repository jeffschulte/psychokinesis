#include "Animation.h"

Animation::Animation() {
    anim_frame_rate = 30; //milliseconds
    current_frame = 0;
    last_frame_time = 0;
    MaxFrames = 12;
    Oscillate = false;
    still_dead = false;

    current_state = 0;
    mini_anim_frame = 0;
    //enum frames {STAND = 0, IN_AIR = 1, HIT_GROUND = 5, GET_UP =8};
    initialize_states_list_values();
}

SDL_Texture* Animation::Animation_Load_Texture(const char* File, SDL_Renderer* renderer) {
    SDL_Texture* texture;
    if((texture = IMG_LoadTexture(renderer, File)) == NULL) {
        return NULL;
    }
    char message[100];
    strcpy (message,"Loaded Entity from ");
    strcat (message,File);
    Logger::log(message);

    return texture;
}

SDL_Rect Animation::Get_Frame_to_Render(double x, double y, double xvel,
                                        double yvel, double height,
                                        int ent_type,bool dead) {
    if(SDL_GetTicks() - last_frame_time < anim_frame_rate){
        SDL_Rect rect =  {68,22+(current_frame)*70,60,60};
        return rect;
    }
    else {
        last_frame_time = SDL_GetTicks();
        if (mini_anim_frame == 0) {
            double targetx = ActionState::p_astate->targetx;
            double targety = ActionState::p_astate->targety;
            double xcont = ActionState::p_astate->xcont;
            EnvLine* line  = Level::p_level->ClosestLine(x, y);
            double dist_to_ground = line->DistToPoint(x, y) - 2.5; //dont understand
            //why this goes down to 2.5 at the ground and stops there.
            current_state = get_next_state(ent_type, targetx, targety,
                                           xcont, dist_to_ground, height,
                                           xvel,yvel,dead);
            if (current_state == P_STAND || current_state == PUSH_R ||
                current_state == PUSH_L || current_state == PUSH_U ||
                current_state == PUSH_D || current_state == FREE_U ||
                current_state == FREE_D || current_state == H_WALL_R ||
                current_state == H_WALL_L || current_state == DEAD ) {
                mini_anim_frame = 0;
            }
            else {
                mini_anim_frame = 1;
            }
            current_frame = states[current_state].beg_frame;
        }
        else {
            current_frame = states[current_state].beg_frame
                + mini_anim_frame - 1;
            mini_anim_frame += 1;
            if (mini_anim_frame == states[current_state].maframe_lim + 1) {
                mini_anim_frame = 0;
                current_state = states[current_state].end_state;
            }
        }
        SDL_Rect rect =  {68,22+(current_frame)*70,60,60};
        return rect;
    }
}



int Animation::get_next_state(int ent_type, double targetx, double targety, double xcont,
                   double dist_to_ground, double height, double xvel,
                              double yvel, bool dead) {
    //int current_state = this->current_state;
    if (still_dead) {
        current_state = DEAD;
    }
    else if (dead) {
        current_state = DYING;
        still_dead = true;
    }
    if (ent_type == Entity::PLAYER) {
        if (dist_to_ground < height/2.0) {
            if (yvel < -20) {
                current_state = HG_FREE_D;
            }
        }
        switch (current_state) {
            case PUSH_R:
                if (targetx < .1) {
                    current_state = STAND_F_PUSH_R;
                }
                break;
            case PUSH_L:
                if (targetx > -.1) {
                    current_state = STAND_F_PUSH_L;
                }
                break;
            case PUSH_U:
                if (targety < .1) {
                    current_state = STAND_F_PUSH_U;
                }
                break;
            case PUSH_D:
                if (targety > -.1) {
                    current_state = STAND_F_PUSH_D;
                }
                break;
            case P_STAND:
                if (targetx >= .1) {
                    current_state = PUSH_R_F_STAND;
                }
                else if (targetx <= -.1) {
                    current_state = PUSH_L_F_STAND;
                }
                else if (targety > .1) {
                    current_state = PUSH_U_F_STAND;
                }
                else if (targety < -.1) {
                    current_state = PUSH_D_F_STAND;
                }
                else if (dist_to_ground < height && xcont > .1) {
                    current_state = RUN_R_F_STAND;
                }
                else if (dist_to_ground < height && xcont < -.1) {
                    current_state = RUN_L_F_STAND;
                }
                else {
                    current_state = P_STAND;
                }
                break;
            case RUN_R:
                if (xcont < .1) {
                    current_state = STAND_F_RUN_R;
                }
                break;
            case RUN_L:
                if (xcont > -.1) {
                    current_state = STAND_F_RUN_L;
                }
                break;
            default:
                break;
        }
    }
    return current_state;
}

void Animation::initialize_states_list_values() {
    states[P_STAND].beg_frame=0; states[P_STAND].maframe_lim=0;
    states[PUSH_R].beg_frame=1; states[PUSH_R].maframe_lim=0;
    states[PUSH_L].beg_frame=2; states[PUSH_L].maframe_lim=0;
    states[PUSH_U].beg_frame=3; states[PUSH_U].maframe_lim=0;
    states[PUSH_D].beg_frame=4; states[PUSH_D].maframe_lim=0;
    states[PUSH_R_F_STAND].beg_frame=5; states[PUSH_R_F_STAND].maframe_lim=3;
    states[STAND_F_PUSH_R].beg_frame=8; states[STAND_F_PUSH_R].maframe_lim=3;
    states[PUSH_L_F_STAND].beg_frame=11; states[PUSH_L_F_STAND].maframe_lim=3;
    states[STAND_F_PUSH_L].beg_frame=14; states[STAND_F_PUSH_L].maframe_lim=3;
    states[PUSH_U_F_STAND].beg_frame=17; states[PUSH_U_F_STAND].maframe_lim=3;
    states[STAND_F_PUSH_U].beg_frame=20; states[STAND_F_PUSH_U].maframe_lim=3;
    states[PUSH_D_F_STAND].beg_frame=23; states[PUSH_D_F_STAND].maframe_lim=3;
    states[STAND_F_PUSH_D].beg_frame=26; states[STAND_F_PUSH_D].maframe_lim=3;
    states[RUN_R].beg_frame=29; states[RUN_R].maframe_lim=5;
    states[RUN_L].beg_frame=34; states[RUN_L].maframe_lim=3;
    states[RUN_R_F_STAND].beg_frame=38; states[RUN_R_F_STAND].maframe_lim=2;
    states[STAND_F_RUN_R].beg_frame=40; states[STAND_F_RUN_R].maframe_lim=3;
    states[RUN_L_F_STAND].beg_frame=43; states[RUN_L_F_STAND].maframe_lim=2;
    states[STAND_F_RUN_L].beg_frame=45; states[STAND_F_RUN_L].maframe_lim=3;
    states[FREE_D].beg_frame=48; states[FREE_D].maframe_lim=1;
    states[FREE_U].beg_frame=49; states[FREE_U].maframe_lim=1;
    states[HG_FREE_D].beg_frame=50; states[HG_FREE_D].maframe_lim=4;
    states[FREE_D_F_STAND].beg_frame=54; states[FREE_D_F_STAND].maframe_lim=2;
    states[STAND_F_FREE_D].beg_frame=56; states[STAND_F_FREE_D].maframe_lim=2;
    states[H_WALL_L].beg_frame=58; states[H_WALL_L].maframe_lim=1;
    states[H_WALL_R].beg_frame=59; states[H_WALL_R].maframe_lim=1;
    states[H_WALL_L_F_STAND].beg_frame=60; states[H_WALL_L_F_STAND].maframe_lim=3;
    states[STAND_F_H_WALL_L].beg_frame=63; states[STAND_F_H_WALL_L].maframe_lim=3;
    states[H_WALL_R_F_STAND].beg_frame=66; states[H_WALL_R_F_STAND].maframe_lim=3;
    states[STAND_F_H_WALL_R].beg_frame=69; states[STAND_F_H_WALL_R].maframe_lim=3;
    states[SWING_L].beg_frame=72; states[SWING_L].maframe_lim=9;
    states[SWING_R].beg_frame=81; states[SWING_R].maframe_lim=9;
    states[HIT_FACE_F_R].beg_frame=90; states[HIT_FACE_F_R].maframe_lim=7;
    states[HIT_FACE_F_L].beg_frame=97; states[HIT_FACE_F_L].maframe_lim=7;
    states[DEAD].beg_frame=110; states[DEAD].maframe_lim=0;
    states[DYING].beg_frame=104; states[DYING].maframe_lim=6;

    states[P_STAND].end_state = P_STAND;
    states[PUSH_R].end_state = PUSH_R;
    states[PUSH_L].end_state = PUSH_L;
    states[PUSH_U].end_state = PUSH_U;
    states[PUSH_D].end_state = PUSH_D;
    states[PUSH_R_F_STAND].end_state = PUSH_R;
    states[STAND_F_PUSH_R].end_state = P_STAND;
    states[PUSH_L_F_STAND].end_state = PUSH_L;
    states[STAND_F_PUSH_L].end_state = P_STAND;
    states[PUSH_U_F_STAND].end_state = PUSH_U;
    states[STAND_F_PUSH_U].end_state = P_STAND;
    states[PUSH_D_F_STAND].end_state = PUSH_D;
    states[STAND_F_PUSH_D].end_state = P_STAND;
    states[RUN_R].end_state = RUN_R;
    states[RUN_L].end_state = RUN_L;
    states[RUN_R_F_STAND].end_state = RUN_R;
    states[STAND_F_RUN_R].end_state = P_STAND;
    states[RUN_L_F_STAND].end_state = RUN_L;
    states[STAND_F_RUN_L].end_state = P_STAND;
    states[FREE_D].end_state = FREE_D;
    states[FREE_U].end_state = FREE_U;
    states[HG_FREE_D].end_state = P_STAND;
    states[FREE_D_F_STAND].end_state = FREE_D;
    states[STAND_F_FREE_D].end_state = P_STAND;
    states[H_WALL_L].end_state = H_WALL_L;
    states[H_WALL_R].end_state = H_WALL_R;
    states[H_WALL_L_F_STAND].end_state = H_WALL_L;
    states[STAND_F_H_WALL_L].end_state = P_STAND;
    states[H_WALL_R_F_STAND].end_state = H_WALL_R;
    states[STAND_F_H_WALL_R].end_state = P_STAND;
    states[SWING_L].end_state = P_STAND;
    states[SWING_R].end_state = P_STAND;
    states[HIT_FACE_F_R].end_state = P_STAND;
    states[HIT_FACE_F_L].end_state = P_STAND;
    states[DEAD].end_state = DEAD;
    states[DYING].end_state = DEAD;
}
