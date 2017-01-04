#ifndef STATE_PLAYING_H
#define STATE_PLAYING_H

#include <memory>

#include "State_Base.h"
#include "World.h"

namespace State
{
    class State_Playing : public State_Base
    {
    private:
        std::unique_ptr<World> m_world;

    public:
        //State_Playing(MainGame* app);
        State_Playing(sf::RenderWindow* window);

        void input()                override;
        void update(const float dt) override;
        void render()               override;
    };
}

#endif // STATE_PLAYING_H
