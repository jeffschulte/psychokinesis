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
        SDL_Texture* texture;

        Entity();
        SDL_Texture* LoadTexture(const char* File,SDL_Renderer* renderer);
        void OnRender(SDL_Renderer* renderer);

        bool collideline(double x, double y, double targetx, double targety);
};
