#include "GameObject.h"
#include "SDL_render.h"

namespace bejeweled {

GameObject::GameObject(int x, int y)
    : m_originX(x), m_originY(y)
{ }

GameObject::~GameObject() = default;

void GameObject::setOrigin(int x, int y) {
    m_originX = x;
    m_originY = y;
}

} // namespace bejeweled
