#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "Engine.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "SDL_render.h"
#include "SDL_video.h"
#include "SurfaceProxy.h"
#include "GameException.h"
#include "GameScene.h"
#include "Point.h"

namespace bejeweled {

const int Engine::GAME_FPS = 20;
const string Engine::WINDOW_TITLE = "Bejeweled";
const string Engine::ICON_IMG = "resources/icon.ico";

Engine::Engine() {
    /// Initialize SDL subsystems.
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) || !IMG_Init(IMG_INIT_PNG) || TTF_Init()) {
        throw GameException();
    }
    
    m_window = SDL_CreateWindow(
        Engine::WINDOW_TITLE.c_str(),
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600,
        SDL_WINDOW_SHOWN);

    if (!m_window) {
        throw GameException();
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

    if (!m_renderer) {
        throw GameException();
    }

    m_resManager = new ResourceManager(m_renderer);

    m_gameIcon = m_resManager->loadSimpleImage(ICON_IMG);

    SDL_SetWindowIcon(m_window, m_gameIcon);

    // Allow playing ogg audio files.
    if(!Mix_Init(MIX_INIT_OGG)) {
        throw GameException();
    }

    // Initialize SDL_mixer
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        throw GameException();
    }

    m_fpsTimer.start();
}

Engine::~Engine() {
    delete m_curScene;
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    Mix_Quit();
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
}

void Engine::run() {
    // Set current scene to the game scene (we only have one scene in this game)
    m_curScene = new GameScene(0, 0, m_resManager);
    if(!m_curScene) {
        throw GameException();
    }

    SDL_Event event;

    // Note - Since we only have one scene (that is, one game state) - this "game over" check will do. 
    // If we had multiple game states, such as introduction screen, main menu, etc., we could adapt the State pattern.
    while(!static_cast<GameScene*>(m_curScene)->isGameover()) {
        m_fpsTimer.start();
        
        /// Engine handles exit events, and calls the handle method of the current scene.
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
            case SDL_QUIT:
                return;
            case SDL_KEYDOWN: 
                if(event.key.keysym.sym == SDLK_F4 && 
                  (event.key.keysym.mod == KMOD_LALT || event.key.keysym.mod == KMOD_RALT)) 
                {
                    return;
                }
            default:
                break;
            }
            m_curScene->handleEvent(&event);
        }

        m_curScene->update();

        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
        SDL_RenderClear(m_renderer);

        m_curScene->draw(m_renderer);

        SDL_RenderPresent(m_renderer);

        // Regulate FPS
        if(m_fpsTimer.getTicks() < 1000.0 / GAME_FPS) {
            SDL_Delay((1000.0 / GAME_FPS) - m_fpsTimer.getTicks());
        }
    }
    
    // Game exit - wait for 2 seconds and then exit.
    SDL_Delay(2000);
}

} // namespace bejeweled