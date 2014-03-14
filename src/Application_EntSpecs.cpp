#include "Application.h"


void Application::Get_Ent_Specs(SDL_Renderer* renderer, Entity* ent,
                   Ent_Types ent_type, double x, double y) {
    if (ent_type > 1.5){
        printf("Error:ent_type is too big\n");
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
    return;
}
