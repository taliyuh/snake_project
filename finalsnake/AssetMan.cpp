#include "AssetMan.h"

Engine::AssetMan::AssetMan(){

}

Engine::AssetMan::~AssetMan(){

}

void Engine::AssetMan::AddTexture(int id, const std::string& filePath, bool wantRepeated){
    auto texture = std::make_unique<sf::Texture>();

    if(texture->loadFromFile(filePath)){
        texture->setRepeated(wantRepeated);
        m_textures[id] = std::move(texture);
    }
}

void Engine::AssetMan::AddFont(int id, const std::string& filePath){
    auto Font = std::make_unique<sf::Font>();

    if(Font->loadFromFile(filePath)){
        m_fonts[id] = std::move(Font);
    }
}

const sf::Texture& Engine::AssetMan::GetTexture(int id) const{
    return *(m_textures.at(id).get());
}

const sf::Font& Engine::AssetMan::GetFont(int id) const {
    auto it = m_fonts.find(id);
    if (it != m_fonts.end()) {
        return *(it->second.get());
    } else {
        std::cout << "Failed to load fonts" << std::endl;
        static sf::Font defaultFont;
        return defaultFont;
    }
}


