#include "Camera.h"


Camera::Camera() {

    /// \todo Put these parameters into the Level class (?)

    x = 12.0;
    y = 8.0;
    zoom = 32.0;
}


/// \todo Make a single transformation method for all three of these.

///
/// Performs same action as \c SDL_RenderCopy, but transforms to
/// screen coordinates first.
///
/// @param renderer the rendering context
/// @param texture the source texture
/// @param srcrect the source rectangle argument
/// @param dstrect the destination rectangle in world coordinates
///
/// @return Returns 0 on success or a negative error code on failure
///
int Camera::RenderCopy(SDL_Renderer* renderer, SDL_Texture* texture,
                       const SDL_Rect* srcrect,
                       const Rect* dstrect) {

    SDL_Rect transrect;

    SDL_GetRendererOutputSize(renderer, &hscreenw, &hscreenh);

    hscreenw /= 2;
    hscreenh /= 2;

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

///
/// Performs same action as \c SDL_RenderFillRect, but transforms to
/// screen coordinates first.
///
/// @param renderer the rendering context
/// @param rect the rectangle to fill in world coordinates
///
/// @return Returns 0 on success or a negative error code on failure
///
int Camera::RenderFillRect(SDL_Renderer* renderer,
                           const Rect* rect) {

    SDL_Rect transrect;

    SDL_GetRendererOutputSize(renderer, &hscreenw, &hscreenh);

    hscreenw /= 2;
    hscreenh /= 2;

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

///
/// Performs same action as \c SDL_RenderDrawLine, but transforms to
/// screen coordinates first.
///
/// @param renderer the rendering context
/// @param x1 x world coordinate of first point
/// @param y1 y world coordinate of first point
/// @param x2 x world coordinate of second point
/// @param y2 y world coordinate of second point
///
/// @return Returns 0 on success or a negative error code on failure
///
int Camera::RenderDrawLine(SDL_Renderer* renderer,
                               double x1,
                               double y1,
                               double x2,
                               double y2) {

    SDL_GetRendererOutputSize(renderer, &hscreenw, &hscreenh);

    hscreenw /= 2;
    hscreenh /= 2;

    return SDL_RenderDrawLine(renderer,
                              (int)((x1-x) * zoom) + hscreenw,
                              (int)((-y1+y) * zoom) + hscreenh,
                              (int)((x2-x) * zoom) + hscreenw,
                              (int)((-y2+y) * zoom) + hscreenh);

}
