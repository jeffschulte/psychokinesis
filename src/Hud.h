#pragma once

#include <SDL.h>
#include "Entity.h"
#include "Camera.h"

// Keeps track of all the pieces that need to be on the hud

class Hud {

    public:

    SDL_Texture* hit_pts_texture;
    SDL_Rect hit_pts_outline_rect;
    SDL_Rect hit_pts_fill_rect;
    SDL_Rect hit_pts_dst_rect;
    double player_starting_hit_pts;
    double hit_pts_meter_width;
    SDL_Texture* Hud_Load_Hit_Pts_Texture(const char* File, SDL_Renderer* renderer,
                                          double player_hit_pts);

    void OnRender(SDL_Renderer* renderer, Camera* camera,
                  double player_x, double player_y,
                  double targetx, double targety, double player_hit_pts);
};
