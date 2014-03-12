#pragma once

#include <SDL.h>
#include <String>
#include "Animation.h"

class Entity {

    public:
        double x, y;            // Position of Entity (CoM)
        double xvel, yvel;      // Velocity
        int width, height;      // Size of Entity
        int old_frame_time;
        int	current_frame;
        std::string debugname;

        int red, green, blue;
        SDL_Texture* texture;
        Animation animation_object;

        Entity();
        SDL_Texture* LoadTexture(const char* File, SDL_Renderer* renderer);
        void OnRender(SDL_Renderer* renderer, int dt);

        bool collideline(double x, double y, double targetx, double targety);
};
