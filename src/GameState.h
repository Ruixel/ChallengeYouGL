#ifndef GAMESTATE_H
#define GAMESTATE_H

class MainGame;

namespace State
{
    class State_Base
    {
    protected:
        MainGame* m_app;

    public:
        State_Base(MainGame* app);

        virtual void input()  = 0;
        virtual void update() = 0;
        virtual void render() = 0;
    };
}

#endif // GAMESTATE_H
