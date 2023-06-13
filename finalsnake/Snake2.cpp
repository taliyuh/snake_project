#include "Snake2.h"

Snake2::Snake2() : m_body(std::list<sf::Sprite>(4))
{
    m_head = --m_body.end();
    m_tail = m_body.begin();
}

Snake2::~Snake2()
{

}

void Snake2::Init(const sf::Texture& texture){
    float x = 600.f;
    float y = 320.f;
    for(auto& piece : m_body){
        piece.setTexture(texture);
        piece.setPosition({x, y});
        x -= 16.f;
    }
}
void Snake2::Move(const sf::Vector2f& direction){
    m_tail->setPosition(m_head->getPosition() + direction);
    m_head = m_tail;
    ++ m_tail;

    if(m_tail == m_body.end()){
        m_tail = m_body.begin();
    }
}
bool Snake2::IsOn(const sf::Sprite& other) const{
    return other.getGlobalBounds().intersects(m_head->getGlobalBounds());
}
void Snake2::Grow(const sf::Vector2f& direction){
    sf::Sprite newPiece;
    newPiece.setTexture(*(m_body.begin()->getTexture()));
    newPiece.setPosition(m_head->getPosition() + direction);
    m_head = m_body.insert(++m_head, newPiece);
}
void Snake2::Grow3(const sf::Vector2f& direction){
    for(int i = 0; i < 3; i++){
    sf::Sprite newPiece;
    newPiece.setTexture(*(m_body.begin()->getTexture()));
    newPiece.setPosition(m_head->getPosition() + direction);
    m_head = m_body.insert(++m_head, newPiece);}
}

bool Snake2::IsSelfIntersecting() const {
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

void Snake2::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for(auto& piece: m_body){
        target.draw(piece);
    }
}

sf::Vector2f Snake2::GetHeadPosition() const
{
    return m_head->getPosition();
}

std::list<sf::Sprite>::iterator Snake2::GetHead()
{
    return m_head;
}
