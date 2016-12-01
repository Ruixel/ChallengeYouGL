#ifndef LOADER_H
#define LOADER_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "RawModel.h"

namespace Loader
{
    GLint createVAO();
    void unbindVAO();

    GLuint storeDataInAttributeList(GLint attributeNumber, int vectorSize,
                                  std::vector<GLfloat>& data);

    GLuint bindIndicesBuffer(std::vector<GLuint>& indices);

    RawModel* loadToVAO(std::vector<GLfloat>& positions, std::vector<GLuint>& indices,
                        std::vector<GLfloat>& texCoords);

    RawModel* loadToVAO(std::vector<GLfloat>& positions, std::vector<GLuint>& indices,
                        std::vector<GLfloat>& texCoords, std::vector<GLfloat>& normals);

    RawModel* loadToVAO(std::vector<GLfloat>& positions, std::vector<GLuint>& indices,
                        std::vector<GLfloat>& texCoords, std::vector<GLfloat>& normals,
                        std::vector<GLfloat>& colors);

    int loadTexture(const GLchar* fileName);

    //std::vector<GLuint> vaos;
    //std::vector<GLuint> vbos;
    //std::vector<GLuint> textures;

    //void cleanUp();
};

#endif // LOADER_H
