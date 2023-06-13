#ifndef ASSETMAN_H
#define ASSETMAN_H
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Font.hpp"
#include <map>
#include <memory>
#include <iostream>
#include <string>

namespace Engine{

class AssetMan{
private:
    std::map<int, std::unique_ptr<sf::Texture>> m_textures;
    std::map<int, std::unique_ptr<sf::Font>> m_fonts;

public:
     const int FRUIT2 = 3;

    AssetMan();
    ~AssetMan();

    void AddTexture(int id, const std::string& filePath, bool wantRepeated = false);
    void AddFont(int id, const std::string& filePath);

    const sf::Texture &GetTexture(int id) const;
    const sf::Font &GetFont(int id) const;
};
}

#endif // ASSETMAN_H
