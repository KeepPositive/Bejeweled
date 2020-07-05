#ifndef __Bejeweled_SurfaceProxy_h__
#define __Bejeweled_SurfaceProxy_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <utility>
#include <string>
#include "SDL2/SDL.h"
#include "Point.h"

namespace bejeweled {

/**
 * Handles loading of Surfaces. 
 * Used to optimize the image to the current display format.
 * Also used for drawing of the surface.
 */
class SurfaceProxy
{
public:    
    /**
     * Proxies the call for IMG_Load. Does NOT optimize the loaded image.
     * This can be safely called before SDL_SetVideoMode (for example, in order to load an icon)
     */
    static SDL_Surface* loadRegularImage(const std::string_view path);

    /**
     * Used to draw the surface according to the given parameters.
     */
    static void draw(int x, int y, SDL_Surface* src, SDL_Surface* dst, SDL_Rect* clip = NULL);

    /**
     * Returns the dimensions of an image at the given path.
     */
    static Point getImageDimensions(const std::string_view path);

private:
    // Prevent Creation, Copying and Assignment
    SurfaceProxy();
    SurfaceProxy(const SurfaceProxy&);
    SurfaceProxy& operator=(const SurfaceProxy&);
}; // class SurfaceProxy

} // namespace bejeweled

#endif // __Bejeweled_SurfaceProxy_h__