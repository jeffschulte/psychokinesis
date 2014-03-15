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
    if (ent_type == PLAYER) {
        if(SDL_GetTicks() - last_frame_time < anim_frame_rate){
            SDL_Rect rect =  {68,22+(current_frame)*70,60,60};
            //68,90,60,60 works on a frame exactly guy pushin right.
            //next frame is man pushing left next down 160 seems to work, so
            //seperation of 70?
            return rect;
        }
        else {
            last_frame_time = SDL_GetTicks();
            //current_frame += 1;
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
