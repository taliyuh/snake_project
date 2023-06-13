#ifndef GAMEOVERDUO_H
#define GAMEOVERDUO_H

#include <memory>
#include <string.h>
#include <SFML/Graphics/Text.hpp>
#include "Game.h"
#include "State.h"

class GameOverDuo : public Engine::State {
private:
    std::shared_ptr<Context> m_context;
    sf::Text m_gameOverTitle;
    sf::Text m_retryButton;
    sf::Text m_GModeButton;
    sf::Text m_exitButton;
    sf::Text m_scoreText;
    sf::Text m_score2Text;
    sf::Text m_winnerText;
    sf::Text m_ultraviolence;

    bool m_isRetryButtonSelected;
    bool m_isRetryButtonPressed;
    bool m_isGModeButtonSelected;
    bool m_isGModeButtonPressed;
    bool m_isExitButtonSelected;
    bool m_isExitButtonPressed;

    int m_score;
    int m_score2;

public:
    GameOverDuo(std::shared_ptr<Context>& context, int score, int score2);
    ~GameOverDuo();

    void Init() override;
    void ProcessInput() override;
    void Update(sf::Time deltaTime) override;
    void Draw() override;
};

#endif // GAMEOVERDUO_H
