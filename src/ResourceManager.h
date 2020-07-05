#ifndef __Bejeweled_ResourceManager__
#define __Bejeweled_ResourceManager__

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <vector>
#include <string_view>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

namespace bejeweled {

/**
 * The resource manager. Used to load and unload images and fonts.
 * There CAN be multiple instances of this class - instead of doing it a singleton.
 * Singleton would yield no added value here and can introduce more problems (destruction, global initialization, etc.).
 */
class ResourceManager
{
public:
    ResourceManager(SDL_Renderer* m_renderer);

    /// frees all the loaded images within the context of this manager instance
    ~ResourceManager();

    /** 
     * Loads an optimized version of the image and saves it in the surfaces vector, 
     * which is freed upon class destruction. This must be called after calling SetVideoMode.
     */
    SDL_Surface* loadImage(const std::string_view path);

    /**
     * Loads a non-optimized version of the image.
     * can be safely called before calling SetVideoMode
     */
    SDL_Surface* loadSimpleImage(const std::string_view path);

    SDL_Texture* loadImageTexture(const std::string_view path);

    /**
     * Loads a font and saves it to the font vector, to be freed upon class destruction.
     * Font path should be a local path.
     */
    TTF_Font* loadFont(const std::string_view path, int size);

    SDL_Texture* loadTextTexture(const std::string_view text, TTF_Font* font, const SDL_Color& fontColor);

    /**
     * Loads a music file and saves it to the music files vector, to be freed upon class destruction.
     * Music file path should be a local path.
     */
    Mix_Music* loadMusic(const std::string_view path);

    /**
     * Loads a music effect file and saves it to the effects files vector, to be freed upon class destruction.
     * Effect file path should be a local path.
     */
    Mix_Chunk* loadEffect(const std::string_view path);


private:
    /// Prevent Copying and Assignment
    ResourceManager(const ResourceManager&);
    ResourceManager& operator=(const ResourceManager&);

    SDL_Renderer* m_renderer;

    std::vector<SDL_Surface*> m_surfaces;
    std::vector<TTF_Font*> m_fonts;
    std::vector<Mix_Music*> m_music;
    std::vector<Mix_Chunk*> m_effects;

}; // class ResourceManager

} // namespace bejeweled

#endif // __Bejeweled_ResourceManager__
