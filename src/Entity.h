#ifndef _ENTITY_H
#define _ENTITY_H

#include <SDL.h>
#include <String>

enum frames {STAND = 0, RUN_RIGHT = 10, RUN_LEFT = 20};

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

        Entity();
        SDL_Texture* LoadTexture(const char* File,SDL_Renderer* renderer);
        void OnRender(SDL_Renderer* renderer);

        bool collideline(double x, double y, double targetx, double targety);
};

#endif
