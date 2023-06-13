#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include <memory>
#include <array>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Game.h"
#include "State.h"
#include "Snake.h"

class GamePlay : public Engine::State{
private:
    std::shared_ptr<Context> m_context;
    sf::Sprite m_grass;
    sf::Sprite m_fruit1;
    sf::Sprite m_fruit2;
    sf::Sprite m_fruit3;
    std::array<sf::Sprite, 4> m_walls;
    Snake m_snake;

    sf::Text m_scoreText;
    int m_score;

    int m_randomNumber;

    sf::Text m_FRuffectText;
    int m_RFuffect;

    sf::Vector2f m_snakeDirection;
    sf::Time m_elapsedTime;
    bool m_canTeleport;

public:
    GamePlay(std::shared_ptr<Context>& context);
    ~GamePlay();

    void Init() override;
    void ProcessInput() override;
    void Update(sf::Time deltaTime) override;
    void Draw() override;
    void TeleportSnake();
    void Start() override;
};

#endif // GAMEPLAY_H
