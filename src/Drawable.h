#ifndef __Bejeweled_Drawable_h__
#define __Bejeweled_Drawable_h__

#include "SDL_render.h"


#include <SDL2/SDL.h>

namespace bejeweled {

/**
 * Interface for drawable objects
 */
class Drawable
{
public:
    virtual void draw(SDL_Renderer* renderer, int x, int y) const = 0;

    /// Destructor
    virtual ~Drawable() {}
}; // class Drawable

} // namespace bejeweled



#endif // __Bejeweled_Drawable_h__