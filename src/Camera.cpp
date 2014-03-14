#include "Camera.h"


Camera::Camera() {

    hscreenw = 320;
    hscreenh = 240;

    x = 12.0;
    y = 12.0;
    zoom = 15.0;
}


int Camera::RenderCopy(SDL_Renderer* renderer, SDL_Texture* texture,
                       const SDL_Rect* srcrect,
                       const Rect* dstrect) {

    SDL_Rect transrect;

    if(dstrect == NULL) {
        return SDL_RenderCopy(renderer, texture, srcrect, NULL);
    }
    else {
        transrect.x = (int)((dstrect->x - x) * zoom) + hscreenw;
        transrect.y = (int)((-dstrect->y + y) * zoom) + hscreenh;
        transrect.w = (int)(dstrect->w * zoom);
        transrect.h = (int)(dstrect->h * zoom);

        return SDL_RenderCopy(renderer, texture, srcrect, &transrect);
    }
}


int Camera::RenderFillRect(SDL_Renderer* renderer,
                           const Rect* rect) {

    SDL_Rect transrect;

    if(rect == NULL) {
        return SDL_RenderFillRect(renderer, NULL);
    }
    else {
        transrect.x = (int)((rect->x - x) * zoom) + hscreenw;
        transrect.y = (int)((-rect->y + y) * zoom) + hscreenh;
        transrect.w = (int)(rect->w * zoom);
        transrect.h = (int)(rect->h * zoom);

        return SDL_RenderFillRect(renderer, &transrect);
    }
}


int Camera::RenderDrawLine(SDL_Renderer* renderer,
                               double x1,
                               double y1,
                               double x2,
                               double y2) {

    return SDL_RenderDrawLine(renderer,
                              (int)((x1-x) * zoom) + hscreenw,
                              (int)((-y1+y) * zoom) + hscreenh,
                              (int)((x2-x) * zoom) + hscreenw,
                              (int)((-y2+y) * zoom) + hscreenh);

}
