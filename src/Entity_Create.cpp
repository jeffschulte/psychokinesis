#include "Entity.h"

Entity* Entity::Create(SDL_Renderer* renderer,
                       EntType type, double x, double y) {

    Entity* ent = new Entity();
    ent->ent_type = type;
    switch (type) {
    case BIG_MAN:
        ent->x = x;
        ent->y = y;
        ent->width = 5;
        ent->height = 5;
        ent->debugname = "big_man";
        if((ent->texture =
            ent->LoadTexture("art_assets/little-man.bmp", renderer)) == NULL) {
            Logger::log("Problem loading texture in Entity_Create");
        }
        break;
    case LITTLE_MAN:
        ent->x = x;
        ent->y = y;
        ent->width = 3;
        ent->height = 3;
        ent->debugname = "little_man";
        if((ent->texture =
            ent->LoadTexture("art_assets/little-man.bmp", renderer)) == NULL) {
            Logger::log("Problem loading texture in Entity_Create");
        }
        break;
    }

    entities.push_back(ent);
    return ent;
}
