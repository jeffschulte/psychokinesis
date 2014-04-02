#pragma once

#include <SDL.h>
#include <Box2D/Box2D.h>
#include <string>
#include <vector>
#include "Camera.h"
#include "Animation.h"
#include "Logger.h"

class Animation;

class Entity {

 public:
    enum EntType {BIG_MAN,LITTLE_MAN,PLAYER};

    static std::vector<Entity*> entities;
    static Entity* Create(SDL_Renderer* renderer,
                          EntType type,double x, double y);

    double x, y;            // Position of Entity (CoM)
    double xforce, yforce;
    double xvel, yvel;      // Velocity
    double width, height;   // Size of Entity
    double angle;           // Angle in degrees
    double mass;


    EntType ent_type;
    bool this_a_player;
    double hit_pts;
    bool dead;

    b2Body* body;

    std::string debugname;

    Uint8 red, green, blue;
    SDL_Texture* texture;
    Entity();

    SDL_Texture* LoadTexture(const char* File,SDL_Renderer* renderer);
    void OnRender(SDL_Renderer* renderer, Camera* camera);

    bool collideline(double x, double y, double targetx, double targety);

    void Calculate_Motion(int dt);

    Animation* animation_object;
};


#include "Player.h"

/// TODO: This is ugly as hell. Fix the coupling....
