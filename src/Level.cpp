#include "Level.h"

EnvLine::EnvLine(double ix1, double iy1, double ix2, double iy2) {
    x1 = ix1;
    y1 = iy1;
    x2 = ix2;
    y2 = iy2;
}

Level* Level::p_level;

Level::Level() : gravity(0.0f, -10.0f), world(gravity) {

    Level::p_level = this;
}


SDL_Texture* Level::LoadAssets(SDL_Renderer* renderer, const char* background,
                               const char* foreground) {

    if((bg = IMG_LoadTexture(renderer, background)) == NULL) {
        return NULL;
    }

    Logger::log("Loaded background");

    return fg = IMG_LoadTexture(renderer, foreground);
}

void Level::OnRender(SDL_Renderer* renderer, Camera* camera) {


    SDL_RenderCopy(renderer, bg, NULL, NULL);

    // For now, we'll just draw a series of lines between the points

    SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255);

    for(int i = 0; i < lines.size(); i++) {
        camera->RenderDrawLine(renderer, lines[i].x1, lines[i].y1,
                               lines[i].x2, lines[i].y2);
    }

    //Rect rect = {0, 34, 40, 40};
    //camera->RenderCopy(renderer, fg, NULL, &rect);

}

void Level::AddLine(double* current_x, double* current_y, double x, double y) {

    lines.push_back(EnvLine(*current_x, *current_y,
                            *current_x + x, *current_y + y));

    b2BodyDef groundbodydef;
    groundbodydef.position.Set(0, 0);

    b2Body* groundbody = world.CreateBody(&groundbodydef);
    b2EdgeShape groundbox;

    groundbox.Set(b2Vec2(*current_x, *current_y),
                  b2Vec2(*current_x + x, *current_y + y));
    groundbody->CreateFixture(&groundbox, 0);
    *current_x += x;
    *current_y += y;
}
