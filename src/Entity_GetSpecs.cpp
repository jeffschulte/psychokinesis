#include "Entity.h"

Entity* Entity::Create_Ent_With_Specs(SDL_Renderer* renderer,
                                     Ent_Types ent_type, double x, double y) {
    Entity* ent = new Entity();
    if (ent_type > 1.5){
        Logger::log("ent_type is too large");
        exit(1);
    }
    switch (ent_type) {
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
    things.push_back(ent);
    return ent;
}
