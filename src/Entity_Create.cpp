#include "Entity.h"
#include "Player.h"

Entity* Entity::Create(SDL_Renderer* renderer,
                       EntType type, double x, double y) {

    Entity* ent;

    switch (type) {
        case BIG_MAN:
            ent = new Entity();
            ent->width = 2;
            ent->height = 2;
            ent->mass = 100;
            ent->hit_pts = 100;
            ent->debugname = "big_man";
            if((ent->texture =
                ent->LoadTexture("art_assets/stickman4sword.png", renderer)) == NULL) {
                Logger::log("Problem loading texture in Entity_Create");
            }
            break;
        case LITTLE_MAN:
            ent = new Entity();
            ent->width = 1.5;
            ent->height = 1.5;
            ent->mass = 90;
            ent->hit_pts = 100;
            ent->debugname = "little_man";
            if((ent->texture =
                ent->LoadTexture("art_assets/stickman4sword.png", renderer)) == NULL) {
                Logger::log("Problem loading texture in Entity_Create");
            }
            break;
        case PLAYER:
            ent = new Entity();
            ent->width = 1.5;
            ent->height = 1.5;
            ent->mass = 90;
            ent->hit_pts = 100;
            ent->debugname = "player";
            ent->this_a_player = true;
            if((ent->texture =
                ent->LoadTexture("art_assets/stickman4sword.png", renderer)) == NULL) {
                Logger::log("Problem loading texture in Entity_Create");
            }
            break;
    }

    ent->ent_type = type;
    ent->x = x;
    ent->y = y;

    // Create its counterpart in the world

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(ent->x, ent->y);
    bodyDef.fixedRotation = true;
    ent->body = Level::p_level->world.CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(ent->width / 2, ent->height / 2);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 3;

    ent->body->CreateFixture(&fixtureDef);

    entities.push_back(ent);
    return ent;
}
