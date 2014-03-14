#include "Entity.h"

Entity* Entity::Create(SDL_Renderer* renderer,
                       EntType type, double x, double y) {

    Entity* ent = new Entity();

    switch (type) {
    case BIG_MAN:
        ent->x = x;
        ent->y = y;
        ent->width = 5;
        ent->height = 5;
        ent->red = 4;
        ent->green = 4;
        ent->blue = 4;
        ent->debugname = "block";
        if((ent->texture =
            ent->LoadTexture("art_assets/little-man.bmp", renderer)) == NULL) {
            Logger::log("Problem loading texture in OnInit");
        }
        break;
    case LITTLE_MAN:
        ent->x = x;
        ent->y = y;
        ent->width = 3;
        ent->height = 3;
        ent->red = 4;
        ent->green = 4;
        ent->blue = 4;
        ent->debugname = "block";
        if((ent->texture =
            ent->LoadTexture("art_assets/little-man.bmp", renderer)) == NULL) {
            Logger::log("Problem loading texture in OnInit");
        }
        break;
    }

    entities.push_back(ent);
    return ent;
}
