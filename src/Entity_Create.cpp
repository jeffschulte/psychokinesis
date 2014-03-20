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
            ent->debugname = "big_man";
            if((ent->texture =
                ent->LoadTexture("art_assets/little-man.bmp", renderer)) == NULL) {
                Logger::log("Problem loading texture in Entity_Create");
            }
            break;
        case LITTLE_MAN:
            ent->motion_object->x = x;
            ent->motion_object->y = y;
            ent->motion_object->width = 1.5;
            ent->motion_object->height = 1.5;
            ent->motion_object->mass = 90;
            ent->debugname = "little_man";
            if((ent->texture =
                ent->LoadTexture("art_assets/little-man.bmp", renderer)) == NULL) {
                Logger::log("Problem loading texture in Entity_Create");
            }
            break;
        case PLAYER:
            ent->motion_object->x = x;
            ent->motion_object->y = y;
            ent->motion_object->width = 1.5;
            ent->motion_object->height = 1.5;
            ent->motion_object->mass = 90;
            ent->debugname = "player";
            ent->this_a_player = true;
            if((ent->texture =
                ent->LoadTexture("art_assets/stickman3sword.png", renderer)) == NULL) {
                Logger::log("Problem loading texture in Entity_Create");
            }
            break;
    }
    entities.push_back(ent);
    return ent;
}
