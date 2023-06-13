#include "GameOver.h"
#include "GamePlay.h"
#include "SoloDuo.h"
#include <SFML/Window/Event.hpp>
#include "GamePlay.h"

GameOver::GameOver(std::shared_ptr<Context> &context)
    : m_context(context), m_isRetryButtonSelected(true), m_isRetryButtonPressed(false),
      m_isExitButtonSelected(false), m_isExitButtonPressed(false), m_bigAssScore(0)
{

}
GameOver::~GameOver()
{

}


void GameOver::Init(){
    m_context -> m_assets -> AddFont(MAIN_FONT, "assets/fonts/Righteous-Regular.ttf");
    //Over Title
    m_gameOverTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_gameOverTitle.setString("Game Over");
    m_gameOverTitle.setOrigin(m_gameOverTitle.getLocalBounds().width / 2, m_gameOverTitle.getLocalBounds().height / 2);
    m_gameOverTitle.setPosition(m_context->m_window->getSize().x / 2 - 10.f, m_context->m_window->getSize().y / 2 - 150.f);
    //Retry
    m_retryButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_retryButton.setString("Play Again");
    m_retryButton.setOrigin(m_retryButton.getLocalBounds().width / 2, m_retryButton.getLocalBounds().height / 2);
    m_retryButton.setPosition(m_context->m_window->getSize().x / 2 + 12.f, m_context->m_window->getSize().y / 2 - 25.f);
    m_retryButton.setCharacterSize(20);
    //GameMode
    m_GModeButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_GModeButton.setString("Game Mode");
    m_GModeButton.setOrigin(m_retryButton.getLocalBounds().width / 2, m_retryButton.getLocalBounds().height / 2);
    m_GModeButton.setPosition(m_context->m_window->getSize().x / 2 - 15.f, m_context->m_window->getSize().y / 2 + 25.f);
    m_GModeButton.setCharacterSize(20);
    //Exit
    m_exitButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_exitButton.setString("Exit");
    m_exitButton.setOrigin(m_exitButton.getLocalBounds().width / 2, m_exitButton.getLocalBounds().height / 2);
    m_exitButton.setPosition(m_context->m_window->getSize().x / 2 - 5, m_context->m_window->getSize().y / 2 + 75.f);
    m_exitButton.setCharacterSize(20);
}

void GameOver::ProcessInput(){
    sf::Event event;
    while(m_context->m_window->pollEvent(event)){
        if(event.type == sf::Event::Closed){
            m_context->m_window->close();
        }
        else if(event.type == sf::Event::KeyPressed){
            switch (event.key.code) {
            case sf::Keyboard::Up:{
                if(m_isGModeButtonSelected){
                    m_isRetryButtonSelected = true;
                    m_isGModeButtonSelected = false;
                    m_isExitButtonSelected = false;
                }else if(m_isExitButtonSelected){
                    m_isRetryButtonSelected = false;
                    m_isGModeButtonSelected = true;
                    m_isExitButtonSelected = false;
                }
                break;
            }
            case sf::Keyboard::W:{
                if(m_isGModeButtonSelected){
                    m_isRetryButtonSelected = true;
                    m_isGModeButtonSelected = false;
                    m_isExitButtonSelected = false;
                }else if(m_isExitButtonSelected){
                    m_isRetryButtonSelected = false;
                    m_isGModeButtonSelected = true;
                    m_isExitButtonSelected = false;
                }
                break;
            }
            case sf::Keyboard::Down:{
                if(m_isRetryButtonSelected){
                    m_isRetryButtonSelected = false;
                    m_isGModeButtonSelected = true;
                    m_isExitButtonSelected = false;
                }else if(m_isGModeButtonSelected){
                    m_isRetryButtonSelected = false;
                    m_isGModeButtonSelected = false;
                    m_isExitButtonSelected = true;
                }

                break;
            }
            case sf::Keyboard::S:{
                if(m_isRetryButtonSelected){
                    m_isRetryButtonSelected = false;
                    m_isGModeButtonSelected = true;
                    m_isExitButtonSelected = false;
                }else if(m_isGModeButtonSelected){
                    m_isRetryButtonSelected = false;
                    m_isGModeButtonSelected = false;
                    m_isExitButtonSelected = true;
                }

                break;
            }
            case sf::Keyboard::Return:{
                m_isRetryButtonPressed = false;
                m_isGModeButtonPressed = false;
                m_isExitButtonPressed = false;
                if(m_isRetryButtonSelected){
                    m_isRetryButtonPressed = true;
                }
                if(m_isGModeButtonSelected){
                    m_isGModeButtonPressed = true;
                }
                if(m_isExitButtonSelected){
                   m_isExitButtonPressed = true;
                }

                break;
            }
            default:
                break;
            }
        }
    }
}
void GameOver::Update(sf::Time deltaTime){
    if(m_isRetryButtonSelected){
        m_retryButton.setFillColor(sf::Color::Yellow);
        m_retryButton.setCharacterSize(24);

        m_GModeButton.setFillColor(sf::Color::White);
        m_retryButton.setCharacterSize(20);
        m_exitButton.setFillColor(sf::Color::White);
    }
    if(m_isGModeButtonSelected){
        m_GModeButton.setFillColor(sf::Color::Yellow);
        m_GModeButton.setCharacterSize(24);

        m_retryButton.setFillColor(sf::Color::White);
        m_GModeButton.setCharacterSize(20);
        m_exitButton.setFillColor(sf::Color::White);
    }
    if(m_isExitButtonSelected){
        m_exitButton.setFillColor(sf::Color::Yellow);
        m_exitButton.setCharacterSize(24);

        m_GModeButton.setFillColor(sf::Color::White);
        m_exitButton.setCharacterSize(20);
        m_retryButton.setFillColor(sf::Color::White);
    }
    if(m_isRetryButtonPressed){
        m_context->m_states->Add(std::make_unique<GamePlay>(m_context), true);
    }
    if(m_isGModeButtonPressed){
        m_context->m_states->Add(std::make_unique<Solo>(m_context), true);
    }
    if(m_isExitButtonPressed){
        m_context->m_window->close();
    }
}
void GameOver::Draw(){
    m_context->m_window->clear(sf::Color::Blue);
    m_context->m_window->draw(m_gameOverTitle);
    m_context->m_window->draw(m_exitButton);
    m_context->m_window->draw(m_GModeButton);
    m_context->m_window->draw(m_retryButton);
    m_context->m_window->display();
}
