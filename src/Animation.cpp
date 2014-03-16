#include "Animation.h"

Animation::Animation() {
    anim_frame_rate = 50; //milliseconds
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

SDL_Rect Animation::Get_Frame_to_Render(double y, double yvel, double height,
                                        int ent_type) {
    if (ent_type == Entity::PLAYER) {
        if(SDL_GetTicks() - last_frame_time < anim_frame_rate){
            SDL_Rect rect =  {68,22+(current_frame)*70,60,60};
            //68,90,60,60 works on a frame exactly guy pushin right.
            //next frame is man pushing left next down 160 seems to work, so
            //seperation of 70?
            return rect;
        }
        // P_STAND=0, PUSH_R=1, PUSH_L=2, PUSH_U=3, PUSH_D=4,
        //                 PUSH_R_F_STAND=5, STAND_F_PUSH_R=8, PUSH_L_F_STAND=11,
        //                 STAND_F_PUSH_L=14, PUSH_U_F_STAND=17, STAND_F_PUSH_U=20,
        //                 PUSH_D_F_STAND=23, STAND_F_PUSH_D=26, RUN_R=29, RUN_L=33,
        //                 RUN_R_F_STAND=37, STAND_F_RUN_R=40, RUN_L_F_STAND=43,
        //                 STAND_F_RUN_L=46, IN_AIR_L=49, IN_AIR_R=50, HGH_R=51,
        //                 HGH_L=54, HGS_R=57, HGS_L=61, WALL_HUG_L=65,
        //                 WALL_HUG_R=66
        //player.yvel -= 2 * 9.8 * astate.targety * dt / 1000.0;
        //player.xvel -= 2 * 9.8 * astate.targetx * dt / 1000.0;
    //  double xcont;
    // bool pushing;
    //xcont, targetx targety are porportional to the joy stick movement itself

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

            current_frame += 1;
            if (current_frame == 50){
                current_frame = 2;
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
