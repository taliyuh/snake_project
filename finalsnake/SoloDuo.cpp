#include "GamePlay.h"
#include "GamePlayDuo.h"
#include "MainMenu.h"
#include <string>
#include <SFML/Window/Event.hpp>
#include "SoloDuo.h"

Solo::Solo(std::shared_ptr<Context> &context)
    : m_context(context), m_isSoloButtonSelected(true), m_isSoloButtonPressed(false),
      m_isDuoButtonSelected(false), m_isDuoButtonPressed(false),
      m_isExitButtonSelected(false), m_isExitButtonPressed(false)
{

}
Solo::~Solo()
{

}

void Solo::Init(){
    m_context -> m_assets -> AddFont(MAIN_FONT, "assets/fonts/Righteous-Regular.ttf");
    //Title
    m_gameTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_gameTitle.setString("GameMode");
    m_gameTitle.setOrigin(m_gameTitle.getLocalBounds().width / 2, m_gameTitle.getLocalBounds().height / 2);
    m_gameTitle.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 150.f);
    //Solo
    m_soloButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_soloButton.setString("Solo");
    m_soloButton.setOrigin(m_soloButton.getLocalBounds().width / 2, m_soloButton.getLocalBounds().height / 2);
    m_soloButton.setPosition(m_context->m_window->getSize().x / 2 + 10.f, m_context->m_window->getSize().y / 2 - 25.f);
    m_soloButton.setCharacterSize(20);
    //Duo
    m_duoButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_duoButton.setString("Duo");
    m_duoButton.setOrigin(m_duoButton.getLocalBounds().width / 2, m_duoButton.getLocalBounds().height / 2);
    m_duoButton.setPosition(m_context->m_window->getSize().x / 2 + 10.f, m_context->m_window->getSize().y / 2 + 25.f);
    m_duoButton.setCharacterSize(20);
    //Exit
    m_exitButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_exitButton.setString(" Go Back");
    m_exitButton.setOrigin(m_exitButton.getLocalBounds().width / 2, m_exitButton.getLocalBounds().height / 2);
    m_exitButton.setPosition(m_context->m_window->getSize().x / 2 + 18.f, m_context->m_window->getSize().y / 2 + 75.f);
    m_exitButton.setCharacterSize(20);
}
void Solo::ProcessInput(){
    sf::Event event;
    while(m_context->m_window->pollEvent(event)){
        if(event.type == sf::Event::Closed){
            m_context->m_window->close();
        }
        else if(event.type == sf::Event::KeyPressed){
            switch (event.key.code) {
            case sf::Keyboard::Up:{
                if(m_isDuoButtonSelected){
                    m_isSoloButtonSelected = true;
                    m_isDuoButtonSelected = false;
                    m_isExitButtonSelected = false;
                } else if(m_isExitButtonSelected){
                    m_isSoloButtonSelected = false;
                    m_isDuoButtonSelected = true;
                    m_isExitButtonSelected = false;
                }
                break;
            }
            case sf::Keyboard::W:{
                if(m_isDuoButtonSelected){
                    m_isSoloButtonSelected = true;
                    m_isDuoButtonSelected = false;
                    m_isExitButtonSelected = false;
                } else if(m_isExitButtonSelected){
                    m_isSoloButtonSelected = false;
                    m_isDuoButtonSelected = true;
                    m_isExitButtonSelected = false;
                }
                break;
            }
            case sf::Keyboard::Down:{
                if(m_isSoloButtonSelected){
                    m_isSoloButtonSelected = false;
                    m_isDuoButtonSelected = true;
                    m_isExitButtonSelected = false;
                } else if(m_isDuoButtonSelected){
                    m_isSoloButtonSelected = false;
                    m_isDuoButtonSelected = false;
                    m_isExitButtonSelected = true;
                }
                break;
            }
            case sf::Keyboard::S:{
                if(m_isSoloButtonSelected){
                    m_isSoloButtonSelected = false;
                    m_isDuoButtonSelected = true;
                    m_isExitButtonSelected = false;
                } else if(m_isDuoButtonSelected){
                    m_isSoloButtonSelected = false;
                    m_isDuoButtonSelected = false;
                    m_isExitButtonSelected = true;
                }
                break;
            }
            case sf::Keyboard::Return:{
                m_isSoloButtonPressed = false;
                m_isDuoButtonPressed = false;
                m_isExitButtonPressed = false;
                if(m_isSoloButtonSelected){
                    m_isSoloButtonPressed = true;
                }
                if(m_isDuoButtonSelected){
                    m_isDuoButtonPressed = true;
                }
                if (m_isExitButtonSelected){
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
void Solo::Update(sf::Time deltaTime){
    if(m_isSoloButtonSelected){
        m_soloButton.setFillColor(sf::Color::Yellow);
        m_soloButton.setCharacterSize(24);

        m_duoButton.setFillColor(sf::Color::White);
        m_soloButton.setCharacterSize(20);
        m_exitButton.setFillColor(sf::Color::White);

    }
    if(m_isDuoButtonSelected){
        m_duoButton.setFillColor(sf::Color::Yellow);
        m_duoButton.setCharacterSize(24);

        m_soloButton.setFillColor(sf::Color::White);
        m_duoButton.setCharacterSize(20);
        m_exitButton.setFillColor(sf::Color::White);
    }
    else if (m_isExitButtonSelected){
        m_exitButton.setFillColor(sf::Color::Yellow);
        m_exitButton.setCharacterSize(24);

        m_soloButton.setFillColor(sf::Color::White);
        m_exitButton.setCharacterSize(20);
        m_duoButton.setFillColor(sf::Color::White);
    }
    if(m_isSoloButtonPressed){
        m_context->m_states->Add(std::make_unique<GamePlay>(m_context), true);

    }
    if(m_isDuoButtonPressed){ // ---------------------------------->DO PODMIANKI <---------------------------------
        m_context->m_states->Add(std::make_unique<GamePlayDuo>(m_context), true);

    }

    if(m_isExitButtonPressed){
        m_context->m_states->Add(std::make_unique<MainMenu>(m_context), true);
    }
}
void Solo::Draw(){
    m_context->m_window->clear(sf::Color::Blue);
    m_context->m_window->draw(m_gameTitle);
    m_context->m_window->draw(m_exitButton);
    m_context->m_window->draw(m_soloButton);
    m_context->m_window->draw(m_duoButton);
    m_context->m_window->display();
}
