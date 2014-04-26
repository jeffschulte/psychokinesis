#pragma once

#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <Box2D/Box2D.h>

#include "Camera.h"
#include "Logger.h"

class EnvLine {

public:
    double x1, x2, y1, y2;

    EnvLine(double ix1, double iy1, double ix2, double iy2);

    //RelLineInfo DistToPoint(double x, double y);
};


class Level {

 public:
    std::vector<EnvLine> lines;

    SDL_Texture* LoadAssets(SDL_Renderer* renderer, const char* background,
                            const char* foreground);

    void OnRender(SDL_Renderer* renderer, Camera* camera);
    void AddLine(double x1, double y1, double x2, double y2);
    Level();
    static Level* p_level;

    b2Vec2 gravity;
    b2World world;

 private:

    SDL_Texture* bg;
    SDL_Texture* fg;
};
