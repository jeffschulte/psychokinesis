#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <Box2D/Box2D.h>
#include "Entity.h"
#include "Camera.h"

class Bullet {

 public:
    static Entity* Create(b2World* worldc, Graphics& graphics,
                          double x, double y,
                          double xvel, double yvel);
};

class StaticRenderComponent : public RenderComponent {

 public:
    virtual void update(Entity& ent, Graphics& graphics);
    StaticRenderComponent(const char* File, Graphics& graphics);

 private:
    SDL_Texture* texture;
};

/*
class Animation;

class Project {

 public:
    enum ProjType {BULLET};

    static Project* Create(SDL_Renderer* renderer,
                           int type, double x, double y,
                           double xvel, double yvel);

    double x, y;            // Position of Projectile (CoM)
    double xforce, yforce;
    double xvel, yvel;      // Velocity
    double width, height;   // Size of Entity
    double anim_width, anim_height; //width and height of animated box
    double angle;           // Angle in degrees
    double mass;
    int stationary_count; //bullet expires when stationary for 3 time steps

    int proj_type;

    b2Body* body;

    std::string debugname;

    Uint8 red, green, blue;
    SDL_Texture* texture;
    Project();

    SDL_Texture* LoadTexture(const char* File,SDL_Renderer* renderer);
    void OnRender(SDL_Renderer* renderer, Camera* camera);

    //bool collideline(double x, double y, double targetx, double targety);

    void Calculate_Motion(int dt);
};
*/
