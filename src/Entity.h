#pragma once

#include <SDL.h>
#include <string>
#include <vector>
#include "Camera.h"
#include "Motion_Calc.h"
#include "Animation.h"
#include "Logger.h"


class Animation;
class Motion_Calc;

class Entity {

 public:
    enum EntType {BIG_MAN,LITTLE_MAN,PLAYER};

    static std::vector<Entity*> entities;
    static Entity* Create(SDL_Renderer* renderer,
                          EntType type,double x, double y);


    /* double x, y;            // Position of Entity (CoM) */
    /* double xvel, yvel;      // Velocity */

    /* double width, height;      // Size of Entity */
    //double mass = 150;
    EntType ent_type;
    bool this_a_player;

    std::string debugname;

    Uint8 red, green, blue;
    SDL_Texture* texture;
    Entity();

    SDL_Texture* LoadTexture(const char* File,SDL_Renderer* renderer);
    void OnRender(SDL_Renderer* renderer, Camera* camera);

    bool collideline(double x, double y, double targetx, double targety);
    Motion_Calc* motion_object;
    void Calculate_Motion(int dt);
private:
    Animation* animation_object;
};
