#include "Entity.h"

Entity* Entity::Create(SDL_Renderer* renderer,
                       EntType type, double x, double y) {

    Entity* ent = new Entity();
    ent->ent_type = type;
    switch (type) {
        case BIG_MAN:
            ent->motion_object->x = x;
            ent->motion_object->y = y;
            ent->motion_object->width = 2;
            ent->motion_object->height = 2;
            ent->motion_object->mass = 100;
            ent->hit_pts = 100;
            ent->debugname = "big_man";
            if((ent->texture =
                ent->LoadTexture("art_assets/stickman4sword.png", renderer)) == NULL) {
                Logger::log("Problem loading texture in Entity_Create");
            }
            break;
        case LITTLE_MAN:
            ent->motion_object->x = x;
            ent->motion_object->y = y;
            ent->motion_object->width = 1.5;
            ent->motion_object->height = 1.5;
            ent->motion_object->mass = 90;
            ent->hit_pts = 100;
            ent->debugname = "little_man";
            if((ent->texture =
                ent->LoadTexture("art_assets/stickman4sword.png", renderer)) == NULL) {
                Logger::log("Problem loading texture in Entity_Create");
            }
            break;
        case PLAYER:
            ent->motion_object->x = x;
            ent->motion_object->y = y;
            ent->motion_object->width = 1.5;
            ent->motion_object->height = 1.5;
            ent->motion_object->mass = 90;
            ent->hit_pts = 100;
            ent->debugname = "player";
            ent->this_a_player = true;
            if((ent->texture =
                ent->LoadTexture("art_assets/stickman4sword.png", renderer)) == NULL) {
                Logger::log("Problem loading texture in Entity_Create");
            }
            break;
    }

    // Create its counterpart in the world

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(ent->motion_object->x, ent->motion_object->y);
    bodyDef.fixedRotation = true;
    ent->body = Level::p_level->world.CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(ent->motion_object->width / 2,
                        ent->motion_object->height / 2);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 3;

    ent->body->CreateFixture(&fixtureDef);

    entities.push_back(ent);
    return ent;
}
