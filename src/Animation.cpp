#include "Animation.h"

Animation::Animation() {
    anim_frame_rate = 5000; //milliseconds
    current_frame = 0;
    last_frame_time = 0;
    MaxFrames = 12;
    Oscillate = false;

    current_state = 0;
    mini_anim_frame = 0;
    //enum frames {STAND = 0, IN_AIR = 1, HIT_GROUND = 5, GET_UP =8};

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
                                        int ent_type) {

    if (ent_type == Entity::PLAYER) {
        // printf("xvel = %g yvel  =%g x = %g y = %g\n",xvel,yvel,x,y);
        if(SDL_GetTicks() - last_frame_time < anim_frame_rate){
            SDL_Rect rect =  {68,22+(current_frame)*70,60,60};
            //68,90,60,60 works on a frame exactly guy pushin right.
            //next frame is man pushing left next down 160 seems to work, so
            //seperation of 70?
            return rect;
        }
        else {
            double targetx = ActionState::p_astate->targetx;
            double targety = ActionState::p_astate->targety;
            double xcont = ActionState::p_astate->xcont;
            EnvLine* line  = Level::p_level->ClosestLine(x, y);
            double dist_to_ground = line->DistToPoint(x, y) - 2.5; //dont understand
            //why this goes down to 2.5 at the ground and stops there.
            // printf("targetx = %g targety = %g xonct = %g dist_to_ground = %g\n",
            //        targetx, targety, xcont, dist_to_ground);
            printf("AAAAA\n");
            // {P_STAND=0, PUSH_R=1, PUSH_L=2, PUSH_U=3, PUSH_D=4,
            //                 PUSH_R_F_STAND=5, STAND_F_PUSH_R=8, PUSH_L_F_STAND=11,
            //                 STAND_F_PUSH_L=14, PUSH_U_F_STAND=17, STAND_F_PUSH_U=20,
            //                 PUSH_D_F_STAND=23, STAND_F_PUSH_D=26, RUN_R=29, RUN_L=33,
            //                 RUN_R_F_STAND=37, STAND_F_RUN_R=40, RUN_L_F_STAND=43,
            //                 STAND_F_RUN_L=46, IN_AIR_L=49, IN_AIR_R=50, HGH_R=51,
            //                 HGH_L=54, HGS_R=57, HGS_L=61, WALL_HUG_L=65,
            //                 WALL_HUG_R=66};
            printf("state = %d  anim = %d\n",current_state,mini_anim_frame);
            if (mini_anim_frame == 0) {
                mini_anim_frame = 1;
                if (dist_to_ground < height/2.0) {
                    if (yvel < -25) {
                        if (current_state == P_STAND || current_state == IN_AIR_R ||
                            current_state == PUSH_R) {
                            current_state = HGH_R;
                        }
                        else {
                            current_state = HGH_L;
                        }
                    }
                    else if (yvel < -10) {
                        printf("yvel = %g\n",yvel);
                        if (current_state == P_STAND || current_state == IN_AIR_R ||
                            current_state == PUSH_R) {
                            current_state = HGS_R;
                        }
                        else {
                            current_state = HGS_L;
                        }
                    }
                }
                switch (current_state) {
                    case PUSH_R:
                        if (targetx < .1) {
                            current_state = STAND_F_PUSH_R;
                        }
                        mini_anim_frame = 0;
                        break;
                    case PUSH_L:
                        if (targetx > -.1) {
                            current_state = STAND_F_PUSH_L;
                        }
                        mini_anim_frame = 0;
                        break;
                    case PUSH_U:
                        if (targety < .1) {
                            current_state = STAND_F_PUSH_U;
                        }
                        mini_anim_frame = 0;
                        break;
                    case PUSH_D:
                        if (targety > -.1) {
                            current_state = STAND_F_PUSH_D;
                        }
                        mini_anim_frame = 0;
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
                        else if (dist_to_ground > height*3 && xvel > 0) {
                            current_state = IN_AIR_R;
                        }
                        else if (dist_to_ground > height*3 && xvel < 0) {
                            current_state = IN_AIR_L;
                        }
                        else {
                            current_state = P_STAND;
                            mini_anim_frame = 0;
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
                    case IN_AIR_R:
                        if (dist_to_ground > height*3 && xvel > 0) {
                            current_state = IN_AIR_R;
                        }
                        else {
                            current_state = P_STAND;
                        }
                        mini_anim_frame = 0;
                    case IN_AIR_L:
                        if (dist_to_ground > height*3 && xvel < 0) {
                            current_state = IN_AIR_L;
                        }
                        current_state = P_STAND;
                        mini_anim_frame = 0;
                    default:
                        break;
                }
            }
            else {
                printf("frame = %d",mini_anim_frame);
                if (current_state == STAND_F_PUSH_R || current_state == STAND_F_PUSH_L ||
                    current_state == STAND_F_PUSH_U || current_state == STAND_F_PUSH_D ||
                    current_state == STAND_F_RUN_R || current_state == STAND_F_RUN_L) {
                    current_frame = current_state + mini_anim_frame-1;
                    mini_anim_frame += 1;
                    if (mini_anim_frame == 4) {
                        mini_anim_frame = 0;
                        current_state = P_STAND;
                    }
                }
                else if (current_state == PUSH_R_F_STAND || current_state == PUSH_L_F_STAND ||
                         current_state == PUSH_U_F_STAND || current_state == PUSH_D_F_STAND ||
                         current_state == RUN_R_F_STAND || current_state == RUN_L_F_STAND ||
                         current_state == HGH_R || current_state == HGH_L) {
                    current_frame = current_state + mini_anim_frame-1;
                    mini_anim_frame += 1;
                    if (mini_anim_frame == 4) {
                        mini_anim_frame = 0;
                        switch (current_state) {
                            case PUSH_R_F_STAND:
                                current_state = PUSH_R;
                                break;
                            case PUSH_L_F_STAND:
                                current_state = PUSH_L;
                                break;
                            case PUSH_U_F_STAND:
                                current_state = PUSH_U;
                                break;
                            case PUSH_D_F_STAND:
                                current_state = PUSH_D;
                                break;
                            case RUN_R_F_STAND:
                                current_state = RUN_R;
                                break;
                            case RUN_L_F_STAND:
                                current_state = RUN_L;
                                break;
                            case HGH_R:
                                current_state = P_STAND;
                                //should just stay dead
                                break;
                            case HGH_L:
                                current_state = P_STAND;
                                break;
                            default:
                                break;
                        }
                    }
                }
                else if (current_state == RUN_R || current_state == RUN_L ||
                         current_state == HGS_R || current_state == HGS_L) {
                    current_frame = current_state + mini_anim_frame-1;
                    mini_anim_frame += 1;
                    if (mini_anim_frame == 5) {
                        mini_anim_frame = 0;
                        switch (current_state) {
                            case RUN_R:
                                current_state = RUN_R;
                                break;
                            case RUN_L:
                                current_state = RUN_L;
                                break;
                            case HGS_R:
                                current_state = P_STAND;
                                break;
                            case HGS_L:
                                current_state = P_STAND;
                                break;
                            default:
                                break;
                        }
                    }
                }
            }
            SDL_Rect rect =  {68,22+(current_frame)*70,60,60};
            return rect;
        }
    }
    else {
        if(SDL_GetTicks() - last_frame_time < anim_frame_rate){
            SDL_Rect rect = {330,100+(current_frame)*197,300,210};//xpos,ypos,width,hieght
            return rect;
        }
        else {
            last_frame_time = SDL_GetTicks();
            if (mini_anim_frame == 0) {
                if (y <= height/2 +.1) {
                    current_state = ON_GROUND;
                }
                else if (y > height/2 + 3 || yvel > 0) {
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
            SDL_Rect rect = {330,100+(current_frame)*197,300,210};//xpos,ypos,width,hieght
            return rect;
        }
    }
}
