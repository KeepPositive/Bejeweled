#include <SDL2/SDL.h>
#include "SDL_render.h"
#include "SDL_surface.h"
#include "SelectedTileView.h"
#include "GameException.h"

namespace bejeweled {

SDL_Color SelectedTileView::TILE_BORDER_COLOR = {100,255,255};
int SelectedTileView::TILE_BORDER_WIDTH = 3;

SelectedTileView::SelectedTileView(SDL_Texture* tileImg) 
: TileView(tileImg) { }

SelectedTileView::SelectedTileView() :  TileView() {
}

SelectedTileView::~SelectedTileView() {
    ///Resource manager destroys SDL objects
}

SelectedTileView::SelectedTileView(const SelectedTileView& other) {
    this->operator=(other);
}

SelectedTileView& SelectedTileView::operator=(const SelectedTileView& other) {
    TileView::operator=(other);
    return *this;
}

void SelectedTileView::draw(SDL_Renderer* renderer, int x, int y) const{
    TileView::draw(renderer, x, y);

    // Now draw some borders.
    int width = 65, height = 65;

    SDL_Rect rects[] = {
        {x, y, TILE_BORDER_WIDTH, height}, // Left
        {x, y, width, TILE_BORDER_WIDTH},  // Top
        {x, y + height - TILE_BORDER_WIDTH, width, TILE_BORDER_WIDTH},
        {x + width - TILE_BORDER_WIDTH, y, TILE_BORDER_WIDTH, height}
    };

    SDL_SetRenderDrawColor(renderer, TILE_BORDER_COLOR.r, TILE_BORDER_COLOR.g, TILE_BORDER_COLOR.b, 255);

    SDL_RenderFillRects(renderer, rects, 4);
}

} // namespace bejeweled
