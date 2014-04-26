#pragma once

#include <SDL.h>
#include <Box2D/Box2D.h>
#include <string>
#include "Graphics.h"
#include "Logger.h"

class Entity;

// These are general components that can be swapped in for the
// different types of entities

class InputComponent
{
 public:
    virtual ~InputComponent() {}
    virtual void update(Entity& ent) = 0;
};

class PhysicsComponent
{
 public:
    virtual ~PhysicsComponent() {}
    virtual void update(Entity& ent) = 0;
};

class RenderComponent
{
 public:
    virtual ~RenderComponent() {}
    virtual void update(Entity& ent, Graphics& graphics) = 0;
};

class Entity {

 public:

    enum EntType {BIG_MAN,LITTLE_MAN,PLAYER};

    Entity(InputComponent* inputc,
           PhysicsComponent* physicsc,
           RenderComponent* renderc);

    void update(Graphics& graphics);

    double x, y, xvel, yvel, width, height, angle, hit_pts;
    bool dead;

    // TODO: Move these someplace less general

    bool this_a_player;

    bool swing_right;
    bool swing_left;
    bool shoot_right;
    bool shoot_left;

    EntType ent_type;
    double mass;
    int proj_shoot_type;

    std::string debugname;

    double anim_width, anim_height;

 private:

    InputComponent* input;
    PhysicsComponent* physics;
    RenderComponent* render;

};


// Next are general components that are applied to everything at the
// moment

class CopyPhysicsComponent : public PhysicsComponent {

 public:

    CopyPhysicsComponent(b2World* worldc);
    virtual void update(Entity& ent);
    void ApplyForce(double x, double y);
    b2Body* getBody() { return body; }
    void Walk(double force, Entity& ent);

    int floorContacts;

 private:

    b2World * world;
    b2Body* body;
};



class NullInputComponent : public InputComponent {

 public:
    virtual void update(Entity& ent);
};

class NullPhysicsComponent : public PhysicsComponent {

 public:
    virtual void update(Entity& ent);
};

class NullRenderComponent : public RenderComponent {

 public:
    virtual void update(Entity& ent, Graphics& graphics);
};
