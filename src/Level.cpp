#include "Level.h"

EnvLine::EnvLine(double ix1, double iy1, double ix2, double iy2) {
    x1 = ix1;
    y1 = iy1;
    x2 = ix2;
    y2 = iy2;
}


RelLineInfo EnvLine::DistToPoint(double x, double y) {
    RelLineInfo closest_pt;
    double lengthsq = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);

    double t = ((x - x1) * (x2 - x1) + (y - y1) * (y2 - y1)) / lengthsq;//dot product

    //below is if x,y is to the left or right of both line end points
    if(t < 0.0) {
        closest_pt.dist_to_pt = sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));
        closest_pt.x_to_pt = x1 - x;
        closest_pt.y_to_pt = y1 - y;
    }
    else if(t > 1.0) {
        closest_pt.dist_to_pt = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
        closest_pt.x_to_pt = x2 - x;
        closest_pt.y_to_pt = y2 - y;
    }
    else {
    //the proj point is the closest on the line to the x,y point
    double projx = x1 + t * (x2 - x1);
    double projy = y1 + t * (y2 - y1);
    closest_pt.x_to_pt = projx - x;
    closest_pt.y_to_pt = projy - y;
    closest_pt.dist_to_pt = sqrt((x - projx) * (x - projx) + (y - projy) * (y - projy));
    }
    return closest_pt;
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

    Rect rect = {0, 34, 40, 40};
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

EnvLine* Level::ClosestLine(double x, double y) {

    double dist = 1.0/0.0;     // Infinity
    EnvLine* closest = NULL;

    for(int i = 0; i < lines.size(); i++) {

        if(lines[i].DistToPoint(x,y).dist_to_pt < dist) {
            closest = &lines[i];
            dist = lines[i].DistToPoint(x,y).dist_to_pt;
        }
    }

    return closest;
}

EnvLine* Level::SecondClosestLine(double x, double y, EnvLine* closest) {

    double dist = 1.0/0.0;     // Infinity
    EnvLine* second_closest = NULL;

    for(int i = 0; i < lines.size(); i++) {
        if( (lines[i].DistToPoint(x,y).dist_to_pt < dist)
           && (&lines[i] != closest) ) {
            second_closest = &lines[i];
            dist = lines[i].DistToPoint(x,y).dist_to_pt;
        }
    }

    return second_closest;
}
