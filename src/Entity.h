#pragma once

#include <SDL.h>
#include "Animation.h"
#include "Logger.h"
#include <string>
#include "Camera.h"
#include <vector>

class Entity {

 public:
    enum EntType {BIG_MAN,LITTLE_MAN,PLAYER};

    static std::vector<Entity*> entities;
    static Entity* Create(SDL_Renderer* renderer,
                          EntType type,double x, double y);


    double x, y;            // Position of Entity (CoM)
    double xvel, yvel;      // Velocity

    double width, height;      // Size of Entity
    EntType ent_type;
    double mass;

    std::string debugname;

    Uint8 red, green, blue;
    SDL_Texture* texture;
    Entity();

    SDL_Texture* LoadTexture(const char* File,SDL_Renderer* renderer);
    void OnRender(SDL_Renderer* renderer, Camera* camera);

    bool collideline(double x, double y, double targetx, double targety);
 private:
    Animation animation_object;
};
