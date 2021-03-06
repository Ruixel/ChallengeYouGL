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
    std::unique_ptr<RawModel>   mesh;
    int             m_textureID = 0;

    // Positional Properties
    glm::vec3       position    = glm::vec3(0,0,0);
    sf::Vector3f    rotation    = sf::Vector3f(0,0,0);
    float           scale       = 1;
    glm::mat4       transformationMatrix;

    // Quick transformation matrix
    void createTransformationMatrix();

    // Loader reference
    //Loader*         mLoader;

public:
    Entity();
    Entity(std::unique_ptr<RawModel> entityMesh, int textureID);

    virtual void update(const float dt)  = 0;
    virtual void draw() = 0;

    glm::vec3   getPosition()                { return position; }
    void        setPosition(glm::vec3 pos)   { position = pos; }
};

#endif // ENTITY_H
