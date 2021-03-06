#ifndef __Bejeweled_GameScene_h__
#define __Bejeweled_GameScene_h__

#include "SDL_render.h"

#include <SDL2/SDL.h>
#include <string>
#include "ResourceManager.h"
#include "GameButton.h"
#include "GameBoard.h"
#include "GameObject.h"

namespace bejeweled {

/**
 * Represents the game scene itself.
 */
class GameScene : public GameObject
{
public:
    /// The path to the background image and to the music
    static const std::string BACKGROUND_IMG;
    static const std::string BACKGROUND_MUSIC;

    /// Constructor
    GameScene(int x, int y, ResourceManager* resourceManager);

    /// Destructor
    virtual ~GameScene();

    /// Indicates if the game is over
    bool isGameover() const;

    /// Inherited Game loop functions 
    virtual void update();
    virtual void draw(SDL_Renderer* renderer);
    virtual void handleEvent(SDL_Event* event);
    virtual bool isPointInObject(int x, int y) const;
    
private:
    /// Prevent Copying and Assignment
    GameScene(const GameScene&);
    GameScene& operator=(const GameScene&);

    /// Indicates if the game over
    bool m_isGameover;

    /// Resource manager for background image and music
    ResourceManager* m_resManager;

    /// Represents the game screens
    SDL_Texture* m_backgroundImage;

    /// Background music
    Mix_Music* m_music;

    /// Objects on the game screen
    GameBoard m_gameBoard;
    GameButton m_button;
}; // class GameScene

} // namespace bejeweled

#endif // __Bejeweled_GameScene_h__
