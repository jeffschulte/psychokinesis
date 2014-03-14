#pragma once

#include <SDL.h>
#include "Animation.h"
#include "Logger.h"
#include <string>
#include "Camera.h"
#include <vector>

class Entity {

    public:
        double x, y;            // Position of Entity (CoM)
        double xvel, yvel;      // Velocity

        double width, height;      // Size of Entity
        std::string debugname;

        int red, green, blue;
        SDL_Texture* texture;
        enum Ent_Types {BIG_MAN,LITTLE_MAN};
        Entity();
        static std::vector<Entity*> things;
        static Entity* Create_Ent_With_Specs(SDL_Renderer* renderer,
                                            Ent_Types ent_type,double x, double y);
        SDL_Texture* LoadTexture(const char* File,SDL_Renderer* renderer);
        void OnRender(SDL_Renderer* renderer, Camera* camera);

        bool collideline(double x, double y, double targetx, double targety);
 private:
        Animation animation_object;
};
