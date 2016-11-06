#include "Entity.h"

Entity::Entity(Loader& loader)
{
    this->mLoader = &loader;
}

Entity::~Entity()
{
    delete mesh;
}

void Entity::createTransformationMatrix()
{
    glm::mat4 matrix;

    matrix = glm::translate  (matrix, position);
    matrix = glm::rotate     (matrix, rotation.x, glm::vec3(1, 0, 0));
    matrix = glm::rotate     (matrix, rotation.y, glm::vec3(0, 1, 0));
    matrix = glm::rotate     (matrix, rotation.z, glm::vec3(0, 0, 1));
    matrix = glm::scale      (matrix, glm::vec3(scale, scale, scale));

    this->transformationMatrix = matrix;
}
