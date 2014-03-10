#ifndef _ENTITY_H
#define _ENTITY_H


#include <SDL.h>

class Entity {
    
    public:
        double x, y;            // Position of Entity (CoM)
        double xvel, yvel;      // Velocity
        int width, height;      // Size of Entity

        Entity();
        void OnRender(SDL_Renderer* renderer);
};

#endif