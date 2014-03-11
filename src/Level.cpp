#include "Level.h"

EnvLine::EnvLine(double ix1, double iy1, double ix2, double iy2) {

    x1 = ix1;
    y1 = iy1;
    x2 = ix2;
    y2 = iy2;
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