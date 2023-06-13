#ifndef GAMEPLAYDUO_H
#define GAMEPLAYDUO_H
#include <memory>
#include <array>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Game.h"
#include "State.h"
#include "Snake.h"
#include "Snake2.h"

class GamePlayDuo : public Engine::State{
private:
    std::shared_ptr<Context> m_context;
    sf::Sprite m_grass;
    sf::Sprite m_fruit1;
    sf::Sprite m_fruit2;
    sf::Sprite m_fruit3;
    std::array<sf::Sprite, 4> m_walls;
    Snake m_snake;
    Snake2 m_snake2;

    sf::Text m_scoreText;
    int m_score;
    sf::Text m_scoreText2;
    int m_score2;

    sf::Text m_FRuffectText;
    int m_RFuffect;
    sf::Text m_FRuffectText2;
    int m_RFuffect2;

    int m_randomNumber;

    sf::Vector2f m_snakeDirection;
    sf::Time m_elapsedTime;
    bool m_canTeleport;

    sf::Vector2f m_snake2Direction;
    sf::Time m_elapsedTime2;
    bool m_canTeleport2;

public:
    GamePlayDuo(std::shared_ptr<Context>& context);
    ~GamePlayDuo();

    void Init() override;
    void ProcessInput() override;
    void Update(sf::Time deltaTime) override;
    void Draw() override;
    void TeleportSnake();
    void TeleportSnake2();
    void Start() override;
};

#endif // GAMEPLAYDUO_H

//#ifndef GAMEPLAYDUO_H
//#define GAMEPLAYDUO_H

//#include <memory>
//#include <SFML/Graphics/Text.hpp>
//#include "Game.h"
//#include "State.h"

//class GamePlayDuo : public Engine::State {
//private:
//    std::shared_ptr<Context> m_context;
//    int m_score;
//    int m_score2;

//    // Other member variables

//public:
//    GamePlayDuo(std::shared_ptr<Context>& context);
//    ~GamePlayDuo();

//    void Init() override;
//    void ProcessInput() override;
//    void Update(sf::Time deltaTime) override;
//    void Draw() override;
//};

//#endif // GAMEPLAYDUO_H
