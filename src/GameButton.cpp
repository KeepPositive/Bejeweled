#include <SDL2/SDL.h>
#include <sstream>
#include <string_view>
#include "GameButton.h"
#include "GameException.h"
#include "SDL_render.h"
#include "SurfaceProxy.h"

namespace bejeweled {

// Initialize default values constants
const int GameButton::FONT_SIZE = 28;
const string GameButton::FONT_PATH = "resources/arial.ttf";
const int GameButton::TEXT_OFFSET_INITIAL = 55;
const int GameButton::TEXT_OFFSET_TIMER = 75;
const int GameButton::TEXT_OFFSET_GAMEOVER = 10;
const int GameButton::TEXT_OFFSET_NOMOVES = 3;
const int GameButton::TEXT_OFFSET_Y = 10;
const std::string GameButton::TIMER_BUTTON_TEXT = "Start";
const int GameButton::BUTTON_OFFSET_X = 25;
const int GameButton::BUTTON_OFFSET_Y = 260;
const int GameButton::BUTTON_SIZE_X = 170;
const int GameButton::BUTTON_SIZE_Y = 60;
const SDL_Color GameButton::TIMER_TEXT_COLOR = {255, 255, 255};
const SDL_Color GameButton::BUTTON_BACKCOLOR = {0, 100, 100};
const float GameButton::GAME_TIME_SECS = 60.0f;



GameButton::GameButton(int x, int y, ResourceManager* resourceManager, 
    int w, int h, const std::string_view text,
    SDL_Color textColor, SDL_Color buttonBackgroundColor) 
    : GameObject(x, y),
    m_resManager(resourceManager),
    m_height(h),
    m_width(w),
    m_font(m_resManager->loadFont(FONT_PATH, FONT_SIZE)),
    m_textColor(textColor),
    m_buttonColor(buttonBackgroundColor),
    m_textTexture(nullptr),
    m_buttonStatus(READY),
    m_textOffsetX(TEXT_OFFSET_INITIAL)
{  
    setText(text);
}

GameButton::~GameButton() {
    SDL_DestroyTexture(m_textTexture);
    // Fonts are closed by the resource manager
}

void GameButton::handleEvent(SDL_Event* event) {
    // No need to make sure that this is a left-click event,  as the GameScene checks that.
    if(!m_gameTimer.isStarted()) {
        m_gameTimer.start();
        m_buttonStatus = TIMER;
        m_textOffsetX = TEXT_OFFSET_TIMER;;
    }
}

void GameButton::update() {
    // Update the timer button text
    if(m_buttonStatus == TIMER) {
        std::ostringstream  time;
        int timeRemaining = static_cast<int>(GAME_TIME_SECS - m_gameTimer.getTicks()/1000.0);
        time << timeRemaining;
        setText(time.str());
        if(timeRemaining == 0) {
            m_gameTimer.stop();
            m_buttonStatus = GAMEOVER;
            setText("Game Over");
            m_textOffsetX = TEXT_OFFSET_GAMEOVER;
        }
    }
}

void GameButton::draw(SDL_Renderer* renderer) {
    SDL_Rect rect;
    rect.h = m_height;
    rect.w = m_width;
    rect.x = BUTTON_OFFSET_X;
    rect.y = BUTTON_OFFSET_Y;

    SDL_SetRenderDrawColor(renderer, m_buttonColor.r, m_buttonColor.g, m_buttonColor.b, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderCopy(renderer, m_textTexture, nullptr, &rect);
}

bool GameButton::isPointInObject(int x, int y) const {
    return (x > m_originX && x < m_originX + m_width &&
            y > m_originY && y < m_originY + m_height);
}

void GameButton::setText(const std::string_view text) {
    if (m_textTexture != nullptr) {
        SDL_DestroyTexture(m_textTexture);
    }

    m_textTexture = m_resManager->loadTextTexture(text, m_font, m_textColor);
}

GameButton::ButtonStatus GameButton::getButtonStatus() const {
    return m_buttonStatus;
}

void GameButton::notifyNoMoves() {
    m_gameTimer.stop();
    m_buttonStatus = NOMOVES;
    setText("No Moves!");
    m_textOffsetX = TEXT_OFFSET_NOMOVES;
}

} //namespace bejeweled
