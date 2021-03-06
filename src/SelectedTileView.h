#ifndef __Bejeweled_SeletedTileView_h__
#define __Bejeweled_SeletedTileView_h__

#include "SDL_render.h"

#include <SDL2/SDL.h>
#include "TileView.h"

namespace bejeweled {

/**
 * Represents a (selected) drawable tile on the game board
 */
class SelectedTileView : public TileView
{
public:
    /**
     * Constructor
     * @param tileImg is the source surface of the tile. It is NOT to be freed by this class.
     */ 
    SelectedTileView(SDL_Texture* tileImg);

    /// Empty ctor for empty tile
    SelectedTileView();

    /// Copy ctor - does not duplicate surface.
    SelectedTileView(const SelectedTileView&);

    /// Assignment operator - does not duplicate surface
    SelectedTileView& operator=(const SelectedTileView&);

    /// Destructor
    virtual ~SelectedTileView();

    /**
     * Draws the tile on the given positions
     * @param x Horizontal origin point
     * @param y Vertical origin point
     */
    virtual void draw(SDL_Renderer* renderer, int x, int y) const;

private:

    /// Color of the selected border and its width
    static SDL_Color TILE_BORDER_COLOR;
    static int TILE_BORDER_WIDTH;

}; // class SelectedTileView

} // namespace bejeweled

#endif // __Bejeweled_SeletedTileView_h__
