#ifndef SOLODUO_H
#define SOLODUO_H
#include <memory>
#include <SFML/Graphics/Text.hpp>
#include "Game.h"
#include "State.h"


class Solo : public Engine::State{
private:
    std::shared_ptr<Context> m_context;
    sf::Text m_gameTitle;
    sf::Text m_soloButton;
    sf::Text m_duoButton;
    sf::Text m_exitButton;

    bool m_isSoloButtonSelected;
    bool m_isSoloButtonPressed;
    bool m_isDuoButtonSelected;
    bool m_isDuoButtonPressed;
    bool m_isExitButtonSelected;
    bool m_isExitButtonPressed;

public:
    Solo(std::shared_ptr<Context>& context);
    ~Solo();

    void Init() override;
    void ProcessInput() override;
    void Update(sf::Time deltaTime) override;
    void Draw() override;
};


#endif // SOLODUO_H
