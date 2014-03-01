//==============================================================================
#include "CApp.h"

//==============================================================================
void CApp::OnRender() {

	// Clear everything

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	// Draw some rectangles for the outside level

	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	int rectwidth = 50;

	SDL_Rect rect = {0, 0, rectwidth, 480};
	SDL_RenderFillRect(renderer, &rect);

	SDL_Rect rect2 = {0, 0, 640, rectwidth};
	SDL_RenderFillRect(renderer, &rect2);

	SDL_Rect rect3 = {640-rectwidth, 0, rectwidth, 480};
	SDL_RenderFillRect(renderer, &rect3);

	SDL_Rect rect4 = {0, 480-rectwidth, 640, rectwidth};
	SDL_RenderFillRect(renderer, &rect4);



	// One for the main character

	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_Rect rect5 = {Mainlocx, Mainlocy, 12, 25};
	SDL_RenderFillRect(renderer, &rect5);


	SDL_RenderPresent(renderer);

}

//==============================================================================
