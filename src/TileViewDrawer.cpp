#include "TileViewDrawer.h"
#include "SelectedTileView.h"
#include "TileView.h"
#include <ctime>
#include <cstdlib>
#include <SDL2/SDL.h>

namespace bejeweled {

TileViewDrawer::TileViewDrawer() {
    std::srand((unsigned int)std::time(0));
}

void TileViewDrawer::addAvailableTileImage(SDL_Texture* img) {
    m_tileViews.push_back(TileView(img));
    m_selectedTileViews.push_back(SelectedTileView(img));
}

int TileViewDrawer::getTileHeight() const {
    if (m_tileViews.empty()) {
        return -1;
    }
    return m_tileViews[0].getHeight();
}

int TileViewDrawer::getTileWidth() const {
    if (m_tileViews.empty()) {
        return -1;
    }
    return m_tileViews[0].getWidth();
}

void TileViewDrawer::drawTile(SDL_Renderer* renderer, int x, int y, int id, int isSelected) const {
    if (m_tileViews.empty() || id < 0 || id > m_tileViews.size()) {
        m_emptyTile.draw(renderer, x, y);
        return;
    }

    if (isSelected) {
        m_selectedTileViews[id].draw(renderer, x, y);
    } else {
        m_tileViews[id].draw(renderer, x, y);
    }
}

} // namespace bejeweled
