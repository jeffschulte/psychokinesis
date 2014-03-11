#pragma once

#include <vector>
#include <SDL.h>


class EnvLine {

public:
    double x1, x2, y1, y2;

    EnvLine(double ix1, double iy1, double ix2, double iy2);
};


class Level {
    
    public:
        std::vector<EnvLine> lines;

        void OnRender(SDL_Renderer* renderer);
        void AddLine(double x1, double y1, double x2, double y2);
};