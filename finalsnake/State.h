#pragma once

#include <SFML/System/Time.hpp>

#ifndef STATE_H
#define STATE_H

namespace Engine{
    class State{
    public:
        State(){};
        virtual ~State(){};

        virtual void Init() = 0;
        virtual void ProcessInput() = 0;
        virtual void Update(sf::Time deltaTime) = 0;
        virtual void Draw() = 0;

        virtual void Start(){};

    };
}

#endif // STATE_H
