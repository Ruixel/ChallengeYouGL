#ifndef ENTITY_H
#define ENTITY_H

#include "RawModel.h"
#include "Loader.h"

#include <glm/common.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class MainGame;

class Entity
{
protected:
    // Entity Properties TBA
    RawModel*       mesh;

    // Positional Properties
    glm::vec3       position;
    sf::Vector3f    rotation;
    float           scale;
    glm::mat4       transformationMatrix;

    // Quick transformation matrix
    void createTransformationMatrix();

    // Loader reference
    Loader*         mLoader;

public:
    Entity(Loader& loader);
    virtual ~Entity();

    virtual void update(const float dt)  = 0;
    virtual void draw() = 0;
};

#endif // ENTITY_H
