#include "Hud.h"


SDL_Texture* Hud::Hud_Load_Hit_Pts_Texture(const char* File, SDL_Renderer* renderer,
                                           double player_hit_pts) {
    SDL_Texture* texture;
    if((hit_pts_texture = IMG_LoadTexture(renderer, File)) == NULL) {
        return NULL;
    }

    char message[100];
    strcpy (message,"Loaded hit pts from ");
    strcat (message,File);
    Logger::log(message);

    // hit_pts_src_rect.x = 72; hit_pts_src_rect.y = 61;
    // hit_pts_src_rect.w = 377; hit_pts_src_rect.h = 92;
    hit_pts_fill_rect.x = 73; hit_pts_fill_rect.y = 61;
    hit_pts_fill_rect.w = 377; hit_pts_fill_rect.h = 92;
    hit_pts_dst_rect.x = 25; hit_pts_dst_rect.y = 25;
    hit_pts_dst_rect.w = 377; hit_pts_dst_rect.h = 92;

    player_starting_hit_pts = player_hit_pts;

    return hit_pts_texture;
}

void Hud::OnRender(SDL_Renderer* renderer, Camera* camera,
                   double player_x, double player_y,
                   double targetx, double targety, double player_hit_pts) {

    double mag = sqrt(targetx*targetx + targety*targety);

    if(mag > .2) {
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 128);
        camera->RenderDrawLine(renderer, player_x + 3 * targetx / mag,
                            player_y + 3 * targety / mag,
                            player_x + 3 * targetx / mag + 10 * targetx,
                            player_y + 3 * targety / mag + 10 * targety);
    }
    if (fabs(player_hit_pts - player_starting_hit_pts) < .00001) {
        SDL_RenderCopy(renderer, hit_pts_texture, &hit_pts_fill_rect, &hit_pts_dst_rect);
    }
    else {
        //each color change for bar is 110 down from last
        hit_pts_fill_rect.y = 281;
        //empty meter is at width = 11 and full width = 377
        double fill_width;
        fill_width = (377.0-11.0)*player_hit_pts/player_starting_hit_pts;
        hit_pts_fill_rect.w = fill_width;
        hit_pts_dst_rect.w = fill_width;
        SDL_RenderCopy(renderer, hit_pts_texture, &hit_pts_fill_rect, &hit_pts_dst_rect);
    }
        // hit_pts_src_rect.y = 171;
    // hit_pts_src_rect.x = 72; hit_pts_src_rect.y = 61;
    // hit_pts_src_rect.w = 377; hit_pts_src_rect.h = 92;


}
