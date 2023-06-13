#ifndef SNAKE_H
#define SNAKE_H
#include <list>
#include "Snake2.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Snake : public sf::Drawable{
private:
    std::list<sf::Sprite> m_body;
    std::list<sf::Sprite>::iterator m_head;
    std::list<sf::Sprite>::iterator m_tail;

public:
    Snake();
    ~Snake();

    void Init(const sf::Texture& texture);
    void Move(const sf::Vector2f& direction);
    bool IsOn(const sf::Sprite& other) const;
    void Grow(const sf::Vector2f& direction);
    void Grow3(const sf::Vector2f& direction);
    bool IsSelfIntersecting() const;
    sf::Vector2f GetHeadPosition() const;
    std::list<sf::Sprite>::iterator GetHead();
    bool IsIntersectingWithSnake2(const Snake2& snake2) const;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // SNAKE_H
