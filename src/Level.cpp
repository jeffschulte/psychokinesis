#include "Level.h"

EnvLine::EnvLine(double ix1, double iy1, double ix2, double iy2) {

    x1 = ix1;
    y1 = iy1;
    x2 = ix2;
    y2 = iy2;
}


double EnvLine::DistToPoint(double x, double y) {

    double lengthsq = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);

    double t = ((x - x1) * (x2 - x1) + (y - y1) * (y2 - y1)) / lengthsq;

    if(t < 0.0) {
        return sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));
    }
    else if(t > 1.0) {
        return sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
    }

    double projx = x1 + t * (x2 - x1);
    double projy = y1 + t * (y2 - y1);

    return sqrt((x - projx) * (x - projx) + (y - projy) * (y - projy));
}


void Level::OnRender(SDL_Renderer* renderer) {

    // For now, we'll just draw a series of lines between the points

    SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255);

    for(int i = 0; i < lines.size(); i++) {
        SDL_RenderDrawLine(renderer, lines[i].x1, lines[i].y1,
                           lines[i].x2, lines[i].y2);
    }
}

void Level::AddLine(double x1, double y1, double x2, double y2) {

    lines.push_back(EnvLine(x1, y1, x2, y2));
}

EnvLine* Level::ClosestLine(double x, double y) {

    double dist = 1.0/0.0;     // Infinity
    EnvLine* closest = NULL;

    for(int i = 0; i < lines.size(); i++) {

        if(lines[i].DistToPoint(x,y) < dist) {
            closest = &lines[i];
            dist = lines[i].DistToPoint(x,y);
        }
    }

    return closest;
}