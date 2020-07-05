#include <utility>
#include "Point.h"
#include "SurfaceProxy.h"
#include "GameException.h"

#include "SDL2/SDL_image.h"

namespace bejeweled {

SDL_Surface* SurfaceProxy::loadRegularImage(const std::string_view path) {
    SDL_Surface* loadedImg = IMG_Load(path.data());
    if(!loadedImg) {
        throw GameException();
    }
    return loadedImg;
}

Point SurfaceProxy::getImageDimensions(const std::string_view path) {
    SDL_Surface* loadedImg = IMG_Load(path.data());
    if(!loadedImg) {
        throw GameException();
    }
    int h = loadedImg->h;
    int w = loadedImg->w;

    SDL_FreeSurface(loadedImg);
    return std::make_pair(w,h);
}

} // namespace bejeweled
