#include "Application.h"
#include <math.h>


void Application::OnRender() {

    // Clear everything

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw some rectangles for the outside level

    //walltop.OnRender(renderer);
    //wallleft.OnRender(renderer);
    //wallright.OnRender(renderer);
    //wallbottom.OnRender(renderer);


    level.OnRender(renderer);

    // Test block

	SDL_Texture* block_texture;
	if((block_texture = block.LoadTexture("art_assets/krebs.bmp", renderer)) == NULL) {
		printf("problem loading texture\n");
		exit(1);
	}
    
	block.OnRender(renderer,block_texture);

    // Render the player

    player.OnRender(renderer,NULL);


    // Targeting line for push direction

    mainhud.OnRender(renderer, player, targetx, targety);

    SDL_RenderPresent(renderer);
}
