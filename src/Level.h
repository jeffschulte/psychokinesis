#pragma once

#include <vector>
#include <SDL.h>


class Level {
    
    public:
        std::vector<double> pointsx;
        std::vector<double> pointsy;

        void OnRender(SDL_Renderer* renderer);
};