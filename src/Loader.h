#ifndef LOADER_H
#define LOADER_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "RawModel.h"

class Loader
{
private:
    std::vector<GLuint> vaos;
    std::vector<GLuint> vbos;
    std::vector<GLuint> textures;

    GLint createVAO();
    void unbindVAO();

    void storeDataInAttributeList(GLint attributeNumber, int vectorSize,
                                  std::vector<GLfloat>& data);

    void bindIndicesBuffer(std::vector<GLuint>& indices);

public:
    Loader();

    RawModel* loadToVAO(std::vector<GLfloat>& positions, std::vector<GLuint>& indices,
                        std::vector<GLfloat>& texCoords);

    RawModel* loadToVAO(std::vector<GLfloat>& positions, std::vector<GLuint>& indices,
                        std::vector<GLfloat>& texCoords, std::vector<GLfloat>& normals);

    int loadTexture(const GLchar* fileName);

    void cleanUp();
};

#endif // LOADER_H
