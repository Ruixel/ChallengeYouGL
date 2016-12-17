#ifndef SKYDOME_H
#define SKYDOME_H

#include "OBJLoader.h"
#include "Entity.h"
#include "StaticShader.h"

class SkyDome : public Entity
{
private:
    StaticShader* shader;

public:
    SkyDome(StaticShader& sh);

    void draw();
    void update(const float dt);
};

#endif // SKYDOME_H
