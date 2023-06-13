//class representing snake
#include "Snake.h"
#include "Snake2.h"

Snake::Snake() : m_body(std::list<sf::Sprite>(4))
{
    m_head = --m_body.end();
    m_tail = m_body.begin();
}

Snake::~Snake()
{

}

//generating snake
void Snake::Init(const sf::Texture& texture){
    float x = 16.f;
    float y = 16.f;
    for(auto& piece : m_body){
        piece.setTexture(texture);
        piece.setPosition({x, y});
        x += 16.f;
    }
}

//moving the snake
void Snake::Move(const sf::Vector2f& direction){
    m_tail->setPosition(m_head->getPosition() + direction);
    m_head = m_tail;
    ++ m_tail;

    if(m_tail == m_body.end()){
        m_tail = m_body.begin();
    }
}

//checking for collision with objects
bool Snake::IsOn(const sf::Sprite& other) const{
    return other.getGlobalBounds().intersects(m_head->getGlobalBounds());
}

//increasing the lenght
void Snake::Grow(const sf::Vector2f& direction){
    sf::Sprite newPiece;
    newPiece.setTexture(*(m_body.begin()->getTexture()));
    newPiece.setPosition(m_head->getPosition() + direction);
    m_head = m_body.insert(++m_head, newPiece);
}
void Snake::Grow3(const sf::Vector2f& direction){
    for(int i = 0; i < 3; i++){
    sf::Sprite newPiece;
    newPiece.setTexture(*(m_body.begin()->getTexture()));
    newPiece.setPosition(m_head->getPosition() + direction);
    m_head = m_body.insert(++m_head, newPiece);}
}

//checking for self-intersection
bool Snake::IsSelfIntersecting() const {
    bool flag = false;
    for(auto piece = m_body.begin(); piece != m_body.end(); ++piece){
        if(m_head != piece){
            flag = IsOn(*piece);
            if(flag){
                break;
            }
        }
    }
    return flag;
}

bool Snake::IsIntersectingWithSnake2(const Snake2& snake2) const {
    for (const auto& piece : m_body) {
        if (snake2.IsOn(piece)) {
            return true;
        }
    }
    return false;
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for(auto& piece: m_body){
        target.draw(piece);
    }
}

sf::Vector2f Snake::GetHeadPosition() const
{
    return m_head->getPosition();
}

std::list<sf::Sprite>::iterator Snake::GetHead()
{
    return m_head;
}
