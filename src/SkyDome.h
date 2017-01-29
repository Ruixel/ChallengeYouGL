#ifndef SKYDOME_H
#define SKYDOME_H

#include "OBJLoader.h"
#include "Entity.h"
#include "gStaticShader.h"

class SkyDome : public Entity
{
private:
    gStaticShader* shader;

public:
    SkyDome(gStaticShader& sh);

    void draw();
    void update(const float dt);
};

#endif // SKYDOME_H
