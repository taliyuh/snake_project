#ifndef SNAKE2_H
#define SNAKE2_H
#include <list>
//#include "Snake.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Snake2 : public sf::Drawable{
private:
    std::list<sf::Sprite> m_body;
    std::list<sf::Sprite>::iterator m_head;
    std::list<sf::Sprite>::iterator m_tail;

public:
    Snake2();
    ~Snake2();

    void Init(const sf::Texture& texture);
    void Move(const sf::Vector2f& direction);
    bool IsOn(const sf::Sprite& other) const;
    void Grow(const sf::Vector2f& direction);
    void Grow3(const sf::Vector2f& direction);
    bool IsSelfIntersecting() const;
    sf::Vector2f GetHeadPosition() const;
    std::list<sf::Sprite>::iterator GetHead();
 //   bool IsIntersectingWithSnake(const Snake& snake) const;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // SNAKE2_H
