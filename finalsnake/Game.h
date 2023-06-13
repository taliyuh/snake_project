#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include "AssetMan.h"
#include "stateman.h"

enum AssetID{
    MAIN_FONT = 0,
    GRASS,
    FRUIT1,
    FRUIT2,
    FRUIT3,
    SNAKE,
    SNAKE2,
    WALL,
};

struct Context{
    std::unique_ptr<Engine::AssetMan> m_assets;
    std::unique_ptr<Engine::StateMan> m_states;
    std::unique_ptr<sf::RenderWindow> m_window;

    Context(){
        m_assets = std::make_unique<Engine::AssetMan>();
        m_states = std::make_unique<Engine::StateMan>();
        m_window = std::make_unique<sf::RenderWindow>();
    }
};

class Game
{
private:
    std::shared_ptr<Context> m_context;
    const sf::Time TIME_PER_FRAME = sf::seconds(1.f/60.f);
public:
    Game();
    ~Game();

    void Run();
};

#endif // GAME_H
