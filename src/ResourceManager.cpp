#include <string>
#include <string_view>
#include <SDL2/SDL.h>
#include "ResourceManager.h"
#include "SDL_render.h"
#include "SDL_surface.h"
#include "SurfaceProxy.h"
#include "GameException.h"

namespace bejeweled {

ResourceManager::ResourceManager(SDL_Renderer* renderer)
    : m_renderer(renderer)
{ }

ResourceManager::~ResourceManager() {
    for(int i=0; i<m_surfaces.size(); ++i) {
        SDL_FreeSurface(m_surfaces.at(i));
    }
    for(int i=0; i<m_fonts.size(); ++i) {
        TTF_CloseFont(m_fonts.at(i));
    }
    for(int i=0; i<m_music.size(); ++i) {
        Mix_FreeMusic(m_music.at(i));
    }
    for(int i=0; i<m_effects.size(); ++i) {
        Mix_FreeChunk(m_effects.at(i));
    }
    m_surfaces.clear();
    m_fonts.clear();
    m_music.clear();
    m_effects.clear();
}

SDL_Surface* ResourceManager::loadImage(const std::string_view path) {
    SDL_Surface* img = SurfaceProxy::loadRegularImage(path);
    m_surfaces.push_back(img);
    return img;
}


SDL_Surface* ResourceManager::loadSimpleImage(const std::string_view path) {
    SDL_Surface* img = SurfaceProxy::loadRegularImage(path);
    m_surfaces.push_back(img);
    return img;
}

SDL_Texture* ResourceManager::loadImageTexture(const std::string_view path) {
    SDL_Surface* img_surface = SurfaceProxy::loadRegularImage(path);

    SDL_Texture* img_texture = SDL_CreateTextureFromSurface(m_renderer, img_surface);

    SDL_FreeSurface(img_surface);

    return img_texture;
}

TTF_Font* ResourceManager::loadFont(const std::string_view path, int size) {
    TTF_Font* font = TTF_OpenFont(path.data(), size);
    if(!font) {
        throw GameException();
    }
    m_fonts.push_back(font);
    return font;
}

SDL_Texture* ResourceManager::loadTextTexture(const std::string_view text, TTF_Font* font, const SDL_Color& fontColor) {
    SDL_Surface* font_surface = TTF_RenderText_Blended(font, text.data(), fontColor);
    
    SDL_Texture* font_texture = SDL_CreateTextureFromSurface(m_renderer, font_surface);

    if(!font_texture) {
        throw GameException();
    }
}

Mix_Music* ResourceManager::loadMusic(const std::string_view path) {
    Mix_Music* music = Mix_LoadMUS(path.data());
    if(!music) {
        throw GameException();
    }
    m_music.push_back(music);
    return music;
}

Mix_Chunk* ResourceManager::loadEffect(const std::string_view path) {
    Mix_Chunk* effect = Mix_LoadWAV(path.data());
    if(!effect) {
        throw GameException();
    }
    m_effects.push_back(effect);
    return effect;
}

} //namespace bejeweled
