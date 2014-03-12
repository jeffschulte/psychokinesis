#include "Camera.h"


Camera::Camera() {

    hscreenw = 320;
    hscreenh = 240;

    x = hscreenw;
    y = hscreenh;
    zoom = 1.0;
}


int Camera::RenderCopy(SDL_Renderer* renderer, SDL_Texture* texture,
                       const SDL_Rect* srcrect,
                       const SDL_Rect* dstrect) {

    SDL_Rect transrect;

    if(dstrect == NULL) {
        return SDL_RenderCopy(renderer, texture, srcrect, NULL);
    }
    else {
        transrect.x = (dstrect->x - x + hscreenw) * zoom;
        transrect.y = (dstrect->y - y + hscreenh) * zoom;
        transrect.w = dstrect->w * zoom;
        transrect.h = dstrect->h * zoom;

        return SDL_RenderCopy(renderer, texture, srcrect, &transrect);
    }
}


int Camera::RenderFillRect(SDL_Renderer* renderer,
                           const SDL_Rect* rect) {

    SDL_Rect transrect;

    if(rect == NULL) {
        return SDL_RenderFillRect(renderer, NULL);
    }
    else {
        transrect.x = (rect->x - x + hscreenw) * zoom;
        transrect.y = (rect->y - y + hscreenh) * zoom;
        transrect.w = rect->w * zoom;
        transrect.h = rect->h * zoom;

        return SDL_RenderFillRect(renderer, &transrect);
    }
}


int Camera::RenderDrawLine(SDL_Renderer* renderer,
                               int x1,
                               int y1,
                               int x2,
                               int y2) {

    return SDL_RenderDrawLine(renderer, (x1-x+hscreenw)*zoom, (y1-y+hscreenh)*zoom,
                              (x2-x+hscreenw)*zoom, (y2-y+hscreenh)*zoom);

}
