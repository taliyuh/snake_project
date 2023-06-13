#include "GamePlayDuo.h"
#include "GameOverDuo.h"
#include <SFML/Window/Event.hpp>
#include <stdlib.h>
#include <time.h>

GamePlayDuo::GamePlayDuo(std::shared_ptr<Context>& context) :
    m_context(context),
    m_snakeDirection({16.f, 0.f}),
    m_elapsedTime(sf::Time::Zero),
    m_score(0),
    m_score2(0),
    m_canTeleport(false),
    m_snake2Direction({-16.f, 0.f,}),
    m_canTeleport2(false)
{
    srand(time(nullptr));
}

GamePlayDuo::~GamePlayDuo()
{

}

void GamePlayDuo::Init(){
    m_context->m_assets->AddTexture(GRASS, "assets/textures/grass.png", true);
    m_context->m_assets->AddTexture(SNAKE, "assets/textures/snake.png");
    m_context->m_assets->AddTexture(SNAKE2, "assets/textures/snake2.png");
    m_context->m_assets->AddTexture(FRUIT1, "assets/textures/fruit1.png");
    m_context->m_assets->AddTexture(FRUIT2, "assets/textures/fruit2.png");
    m_context->m_assets->AddTexture(FRUIT3, "assets/textures/fruit3.png");
    m_context->m_assets->AddTexture(WALL, "assets/textures/wall.png", true);

    m_grass.setTexture(m_context->m_assets->GetTexture(GRASS));
    m_grass.setTextureRect(m_context->m_window->getViewport(m_context->m_window->getDefaultView()));

    for(auto& wall : m_walls){
        wall.setTexture(m_context->m_assets->GetTexture(WALL));
    }
    m_walls[0].setTextureRect({0, 0, static_cast<int>(m_context->m_window->getSize().x), 16});
    m_walls[1].setTextureRect({0, 0, static_cast<int>(m_context->m_window->getSize().x), 16});
    m_walls[1].setPosition(0, m_context->m_window->getSize().y - 16);

    m_walls[2].setTextureRect({0, 0, 16, static_cast<int>(m_context->m_window->getSize().y)});
    m_walls[3].setTextureRect({0, 0, 16, static_cast<int>(m_context->m_window->getSize().y)});
    m_walls[3].setPosition(m_context->m_window->getSize().x - 16, 0);

    m_fruit1.setTexture(m_context->m_assets->GetTexture(FRUIT1));
    m_fruit1.setPosition(m_context->m_window->getSize().x/2, m_context->m_window->getSize().y/2);

    m_fruit2.setTexture(m_context->m_assets->GetTexture(FRUIT2));
    m_fruit2.setPosition(m_context->m_window->getSize().x/3, m_context->m_window->getSize().y/3);

    m_fruit3.setTexture(m_context->m_assets->GetTexture(FRUIT3));
    m_fruit3.setPosition(m_context->m_window->getSize().x/4, m_context->m_window->getSize().y/4);

    m_snake.Init(m_context->m_assets->GetTexture(SNAKE));


    m_snake2.Init(m_context->m_assets->GetTexture(SNAKE2));


    m_scoreText.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_scoreText.setString("Score1: " + std::to_string(m_score));
    m_scoreText.setCharacterSize(15);

    m_scoreText2.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_scoreText2.setString("Score2: " + std::to_string(m_score2));
    m_scoreText2.setCharacterSize(15);
    m_scoreText2.setPosition(m_context->m_window->getSize().x/2 + 245.f , m_context->m_window->getSize().y/10 -35.f );

    m_FRuffectText.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_FRuffectText.setString("Fruit3");
    m_FRuffectText.setCharacterSize(15);
    m_FRuffectText.setPosition(m_context->m_window->getSize().x/16 - 40.f, m_context->m_window->getSize().y/10 - 15.f);

    m_FRuffectText2.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_FRuffectText2.setString("Fruit3");
    m_FRuffectText2.setCharacterSize(15);
    m_FRuffectText2.setPosition(m_context->m_window->getSize().x/2 + 275.f, m_context->m_window->getSize().y/10 -15.f );
}

void GamePlayDuo::ProcessInput(){
    sf::Event event;
    while(m_context->m_window->pollEvent(event)){
        if(event.type == sf::Event::Closed){
            m_context->m_window->close();
        }
        else if(event.type == sf::Event::KeyPressed){
            sf::Vector2f newDirection = m_snakeDirection;
            sf::Vector2f newDirection2 = m_snake2Direction;
            switch (event.key.code) {
            case sf::Keyboard::Up:     // --------> for snake2 <--------------
                newDirection2 = {0.f, -16.f};
                break;
            case sf::Keyboard::Down:
                newDirection2 = {0.f, 16.f};
                break;
            case sf::Keyboard::Left:
                newDirection2 = {-16.f, 0.f,};
                break;
            case sf::Keyboard::Right:
                newDirection2 = {16.f, 0.f,};
                break;
            case sf::Keyboard::W:      // --------> for snake1 <--------------
                newDirection = {0.f, -16.f};
                break;
            case sf::Keyboard::S:
                newDirection = {0.f, 16.f};
                break;
            case sf::Keyboard::A:
                newDirection = {-16.f, 0.f,};
                break;
            case sf::Keyboard::D:
                newDirection = {16.f, 0.f,};
                break;
            default:
                break;
            }

            if(std::abs(m_snakeDirection.x) != std::abs(newDirection.x) ||
                   std::abs(m_snakeDirection.y) != std::abs(newDirection.y)){
                m_snakeDirection = newDirection;

            }
            if(std::abs(m_snake2Direction.x) != std::abs(newDirection2.x) ||
                   std::abs(m_snake2Direction.y) != std::abs(newDirection2.y)){
                m_snake2Direction = newDirection2;
            }
        }
    }
}

void GamePlayDuo::TeleportSnake() {
    sf::Vector2f snakeHeadPosition = m_snake.GetHeadPosition();
    sf::Vector2f windowSize = sf::Vector2f(m_context->m_window->getSize());

    if (snakeHeadPosition.x <= 0) {
        snakeHeadPosition.x = windowSize.x - 32;
    }
    else if (snakeHeadPosition.x >= windowSize.x - 16) {
        snakeHeadPosition.x = 16;
    }

    if (snakeHeadPosition.y <= 0) {
        snakeHeadPosition.y = windowSize.y - 32;
    }
    else if (snakeHeadPosition.y >= windowSize.y - 16) {
        snakeHeadPosition.y = 16;
    }

    m_snake.GetHead()->setPosition(snakeHeadPosition);
}

void GamePlayDuo::TeleportSnake2() {
    sf::Vector2f snake2HeadPosition = m_snake2.GetHeadPosition();
    sf::Vector2f windowSize = sf::Vector2f(m_context->m_window->getSize());

    if (snake2HeadPosition.x <= 0) {
        snake2HeadPosition.x = windowSize.x - 32;
    }
    else if (snake2HeadPosition.x >= windowSize.x - 16) {
        snake2HeadPosition.x = 16;
    }

    if (snake2HeadPosition.y <= 0) {
        snake2HeadPosition.y = windowSize.y - 32;
    }
    else if (snake2HeadPosition.y >= windowSize.y - 16) {
        snake2HeadPosition.y = 16;
    }

    m_snake2.GetHead()->setPosition(snake2HeadPosition);
}

void GamePlayDuo::Update(sf::Time deltaTime) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    m_elapsedTime += deltaTime;
    if (m_elapsedTime.asSeconds() > 0.1) {
        bool isOnWall = false;
        for (auto& wall : m_walls) {
            if (!m_canTeleport) {
                if (m_snake.IsOn(wall)) {
                    m_score2 += 5;
                    m_context->m_states->Add(std::make_unique<GameOverDuo>(m_context, m_score, m_score2), true);
                    break;
                    }
                } else {
                    if (m_snake.IsOn(wall)) {
                        TeleportSnake();
                        m_canTeleport = false;
                    }
                }
            if (!m_canTeleport2) {
                if (m_snake2.IsOn(wall)) {
                    m_score += 5;
                    m_context->m_states->Add(std::make_unique<GameOverDuo>(m_context, m_score, m_score2), true);
                    break;
                    }
                } else {
                    if (m_snake2.IsOn(wall)) {
                        TeleportSnake2();
                        m_canTeleport2 = false;
                    }
                }
            }

        //--------------------------------------------------------------FOR SNAKE1-----------------------------------------------------------


        if (m_snake.IsOn(m_fruit1)) {
            m_snake.Grow(m_snakeDirection);

            int x = 0, y = 0;

            int windowWidth = m_context->m_window->getSize().x;
            int windowHeight = m_context->m_window->getSize().y;
            int minX = 14;
            int maxX = windowWidth - 2 * 14;
            int minY = 14;
            int maxY = windowHeight - 2 * 14;

            x = std::clamp<int>(rand() % (maxX - minX) + minX, minX, maxX);
            y = std::clamp<int>(rand() % (maxY - minY) + minY, minY, maxY);

            m_fruit1.setPosition(x, y);
            m_randomNumber = std::rand() % 10;
            m_score += 1;
            m_scoreText.setString("Score1: " + std::to_string(m_score));
        }

        if (m_snake.IsOn(m_fruit2)) {
            m_snake.Grow3(m_snakeDirection);

            int x = 0, y = 0;

            int windowWidth = m_context->m_window->getSize().x;
            int windowHeight = m_context->m_window->getSize().y;
            int minX = 14;
            int maxX = windowWidth - 2 * 14;
            int minY = 14;
            int maxY = windowHeight - 2 * 14;

            x = std::clamp<int>(rand() % (maxX - minX) + minX, minX, maxX);
            y = std::clamp<int>(rand() % (maxY - minY) + minY, minY, maxY);

            // Make sure fruit2 is not at the same position as fruit1
            while (x == m_fruit1.getPosition().x && y == m_fruit1.getPosition().y) {
                x = std::clamp<int>(rand() % m_context->m_window->getSize().x, 14, rand() % m_context->m_window->getSize().x - 2 * 14);
                y = std::clamp<int>(rand() % m_context->m_window->getSize().y, 14, rand() % m_context->m_window->getSize().y - 2 * 14);
            }

            m_fruit2.setPosition(x, y);
            m_randomNumber = std::rand() % 10;
            m_score += 3;
            m_scoreText.setString("Score1: " + std::to_string(m_score));

        }

        if (m_snake.IsOn(m_fruit3)) {
                    m_canTeleport = true;

                    int x = 0, y = 0;

                    int windowWidth = m_context->m_window->getSize().x;
                    int windowHeight = m_context->m_window->getSize().y;
                    int minX = 14;
                    int maxX = windowWidth - 2 * 14;
                    int minY = 14;
                    int maxY = windowHeight - 2 * 14;

                    x = std::min(std::max(rand() % (maxX - minX) + minX, minX), maxX);
                    y = std::min(std::max(rand() % (maxY - minY) + minY, minY), maxY);

                    m_fruit3.setPosition(x, y);
                    m_randomNumber = std::rand() % 10;
                }
                else {
                    m_snake.Move(m_snakeDirection);

                }

        if (m_snake.IsSelfIntersecting()) {
            //m_context->m_states->Add(std::make_unique<GameOverDuo>(m_context), true);
            m_context->m_states->Add(std::make_unique<GameOverDuo>(m_context, m_score, m_score2), true);
        }
//        if (m_snake.IsIntersectingWithSnake2()) {                                  ---------------kolizja z snake2 ---------------------
//            m_context->m_states->Add(std::make_unique<GameOver>(m_context), true);
//        }

        //--------------------------------------------------------FOR SNAKE2------------------------------------
        if (m_snake2.IsOn(m_fruit1)) {
            m_snake2.Grow(m_snake2Direction);

            int x = 0, y = 0;

            int windowWidth = m_context->m_window->getSize().x;
            int windowHeight = m_context->m_window->getSize().y;
            int minX = 14;
            int maxX = windowWidth - 2 * 14;
            int minY = 14;
            int maxY = windowHeight - 2 * 14;

            x = std::clamp<int>(rand() % (maxX - minX) + minX, minX, maxX);
            y = std::clamp<int>(rand() % (maxY - minY) + minY, minY, maxY);

            m_fruit1.setPosition(x, y);
            m_randomNumber = std::rand() % 10;
            m_score2 += 1;
            m_scoreText2.setString("Score2: " + std::to_string(m_score2));
        }

        if (m_snake2.IsOn(m_fruit2)) {
            m_snake2.Grow3(m_snake2Direction);

            int x = 0, y = 0;

            int windowWidth = m_context->m_window->getSize().x;
            int windowHeight = m_context->m_window->getSize().y;
            int minX = 14;
            int maxX = windowWidth - 2 * 14;
            int minY = 14;
            int maxY = windowHeight - 2 * 14;

            x = std::clamp<int>(rand() % (maxX - minX) + minX, minX, maxX);
            y = std::clamp<int>(rand() % (maxY - minY) + minY, minY, maxY);

            // Make sure fruit2 is not at the same position as fruit1
            while (x == m_fruit1.getPosition().x && y == m_fruit1.getPosition().y) {
                x = std::clamp<int>(rand() % m_context->m_window->getSize().x, 14, rand() % m_context->m_window->getSize().x - 2 * 14);
                y = std::clamp<int>(rand() % m_context->m_window->getSize().y, 14, rand() % m_context->m_window->getSize().y - 2 * 14);
            }

            m_fruit2.setPosition(x, y);
            m_randomNumber = std::rand() % 10;
            m_score2 += 3;
            m_scoreText2.setString("Score2: " + std::to_string(m_score2));

        }

        if (m_snake2.IsOn(m_fruit3)) {
                    m_canTeleport2 = true;

                    int x = 0, y = 0;

                    int windowWidth = m_context->m_window->getSize().x;
                    int windowHeight = m_context->m_window->getSize().y;
                    int minX = 14;
                    int maxX = windowWidth - 2 * 14;
                    int minY = 14;
                    int maxY = windowHeight - 2 * 14;

                    x = std::min(std::max(rand() % (maxX - minX) + minX, minX), maxX);
                    y = std::min(std::max(rand() % (maxY - minY) + minY, minY), maxY);

                    m_fruit3.setPosition(x, y);
                    m_randomNumber = std::rand() % 10;
                }
                else {
                    m_snake2.Move(m_snake2Direction);

                }

        if (m_snake2.IsSelfIntersecting()) {
            //m_context->m_states->Add(std::make_unique<GameOverDuo>(m_context), true);
            m_context->m_states->Add(std::make_unique<GameOverDuo>(m_context, m_score, m_score2), true);
        }

        m_elapsedTime = sf::Time::Zero;
    }
}

void GamePlayDuo::Draw(){
    m_context->m_window->clear();
    m_context->m_window->draw(m_grass);
    for(auto& wall : m_walls){
        m_context->m_window->draw(wall);
    }
    if(m_randomNumber == 0 ||m_randomNumber == 1||m_randomNumber == 2||m_randomNumber == 3 ||m_randomNumber == 4||m_randomNumber == 5||m_randomNumber == 6){
        m_context->m_window->draw(m_fruit1);
    }
    if(m_randomNumber == 7||m_randomNumber == 8){
        m_context->m_window->draw(m_fruit2);
    }
    if(m_randomNumber == 9){
        m_context->m_window->draw(m_fruit3);
    }
    m_context->m_window->draw(m_snake);
    m_context->m_window->draw(m_snake2);
    m_context->m_window->draw(m_scoreText);
    m_context->m_window->draw(m_scoreText2);
    if(m_canTeleport){
    m_context->m_window->draw(m_FRuffectText);
    }
    if(m_canTeleport2){
    m_context->m_window->draw(m_FRuffectText2);
    }
    m_context->m_window->display();

}


void GamePlayDuo::Start(){

}

