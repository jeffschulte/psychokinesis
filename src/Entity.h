#pragma once

#include <SDL.h>
#include <String>

class Entity {

    public:
        double x, y;            // Position of Entity (CoM)
        double xvel, yvel;      // Velocity
        int width, height;      // Size of Entity
        std::string debugname;

        int red, green, blue;

        Entity();
        void OnRender(SDL_Renderer* renderer);

        bool collideline(double x, double y, double targetx, double targety);
};
