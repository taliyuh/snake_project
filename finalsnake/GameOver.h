#ifndef MAINMENU_H
#define MAINMENU_H
#include <memory>
#include <SFML/Graphics/Text.hpp>
#include "Game.h"
#include "State.h"


class GameOver : public Engine::State{
private:
    std::shared_ptr<Context> m_context;
    sf::Text m_gameOverTitle;
    sf::Text m_retryButton;
    sf::Text m_GModeButton;
    sf::Text m_exitButton;

    int m_bigAssScore;

    bool m_isRetryButtonSelected;
    bool m_isRetryButtonPressed;
    bool m_isGModeButtonSelected;
    bool m_isGModeButtonPressed;
    bool m_isExitButtonSelected;
    bool m_isExitButtonPressed;

public:
    GameOver(std::shared_ptr<Context>& context);
    ~GameOver();

    void Init() override;
    void ProcessInput() override;
    void Update(sf::Time deltaTime) override;
    void Draw() override;
};

#endif // MAINMENU_H
