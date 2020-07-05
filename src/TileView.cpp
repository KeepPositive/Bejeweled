#include <SDL2/SDL.h>
#include "SDL_render.h"
#include "TileView.h"
#include "GameException.h"
#include "SurfaceProxy.h"

namespace bejeweled {

TileView::TileView(SDL_Texture* tileImg) 
: m_tileImg(tileImg), m_isEmpty(false), m_w(65), m_h(65) {
    // SDL_QueryTexture(tileImg, nullptr, nullptr, &m_w, &m_h);
}

TileView::TileView() : m_isEmpty(true), m_tileImg(NULL) {
}

TileView::~TileView() {
    ///Resource manager destroys SDL objects
}

TileView::TileView(const TileView& other) {
    this->operator=(other);
}

TileView& TileView::operator=(const TileView& other) {
    if(this != &other) {
        m_tileImg = other.m_tileImg;
        m_isEmpty = other.m_isEmpty;
    }
    return *this;
}

void TileView::draw(SDL_Renderer* renderer, int x, int y) const {
    if(!m_isEmpty) {
        SDL_Rect rect{x, y, 65, 65};
        SDL_RenderCopy(renderer, m_tileImg, nullptr, &rect);
    }
}

int TileView::getWidth() const {
    return m_w;
}
int TileView::getHeight() const {
    return m_h;
}

} // namespace bejeweled
