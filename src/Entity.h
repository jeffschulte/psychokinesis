#pragma once

#include <SDL.h>
#include "Animation.h"
#include <string>

#include "Camera.h"

class Entity {

    public:
        double x, y;            // Position of Entity (CoM)
        double xvel, yvel;      // Velocity

        int width, height;      // Size of Entity
        int last_frame_time;
        int	current_frame;
        std::string debugname;

        int red, green, blue;
        SDL_Texture* texture;
        Animation animation_object;

        Entity();
        SDL_Texture* LoadTexture(const char* File,SDL_Renderer* renderer);
        void OnRender(SDL_Renderer* renderer, Camera* camera);

        bool collideline(double x, double y, double targetx, double targety);
};
