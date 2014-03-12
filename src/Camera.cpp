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
        transrect.x = (dstrect->x - x) * zoom + hscreenw;
        transrect.y = (-dstrect->y + y) * zoom + hscreenh;
        transrect.w = dstrect->w * zoom;
        transrect.h = dstrect->h * zoom;

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
        transrect.x = (rect->x - x) * zoom + hscreenw;
        transrect.y = (-rect->y + y) * zoom + hscreenh;
        transrect.w = rect->w * zoom;
        transrect.h = rect->h * zoom;

        return SDL_RenderFillRect(renderer, &transrect);
    }
}


int Camera::RenderDrawLine(SDL_Renderer* renderer,
                               double x1,
                               double y1,
                               double x2,
                               double y2) {

    return SDL_RenderDrawLine(renderer, (x1-x)*zoom+hscreenw, (-y1+y)*zoom+hscreenh,
                              (x2-x)*zoom+hscreenw, (-y2+y)*zoom+hscreenh);

}
