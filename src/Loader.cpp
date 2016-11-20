#include "Loader.h"

RawModel* Loader::loadToVAO(std::vector<GLfloat>& positions, std::vector<GLuint>& indices,
                            std::vector<GLfloat>& texCoords)
{
    GLint vaoID = createVAO();

    // VBOs
    GLuint vboInd  = bindIndicesBuffer(indices);
    GLuint vboVPos = storeDataInAttributeList(0, 3, positions);
    GLuint vboVTex = storeDataInAttributeList(1, 2, texCoords);
    unbindVAO();

    std::cout << "Don't use this please" << std::endl;

    return new RawModel(vaoID, indices.size(), vboVPos, vboVTex, vboInd);
}

RawModel* Loader::loadToVAO(std::vector<GLfloat>& positions, std::vector<GLuint>& indices,
                            std::vector<GLfloat>& texCoords, std::vector<GLfloat>& normals)
{
    GLint vaoID = createVAO();

    // VBOs
    GLuint vboInd  = bindIndicesBuffer(indices);
    GLuint vboVPos = storeDataInAttributeList(0, 3, positions);
    GLuint vboVTex = storeDataInAttributeList(1, 2, texCoords);
    GLuint vboVNrm = storeDataInAttributeList(2, 3, normals);
    unbindVAO();

    return new RawModel(vaoID, indices.size(), vboVPos, vboVTex, vboInd, vboVNrm);
}

GLint Loader::createVAO()
{
    GLuint vaoID;
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    //this->vaos.push_back(vaoID);

    return vaoID;
}

void Loader::unbindVAO()
{
    glBindVertexArray(0);
}

GLuint Loader::bindIndicesBuffer(std::vector<GLuint>& indices)
{
    GLuint vboID;
    glGenBuffers(1, &vboID);

    //this->vbos.push_back(vboID);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);

    return vboID;
}

GLuint Loader::storeDataInAttributeList(GLint attributeNumber, int vectorSize, std::vector<GLfloat>& data)
{
    // generate VBO & tell openGL we're working with it
    GLuint vboID;
    glGenBuffers(1, &vboID);
    //this->vaos.push_back(vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);

    // give the VBO the data that we have
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * data.size(), data.data(), GL_STATIC_DRAW);

    // tell that VAO what to do with this VBO and where to store it
    glVertexAttribPointer(attributeNumber, vectorSize, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(attributeNumber);

    // unbind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return vboID;
}

int Loader::loadTexture(const GLchar* fileName)
{
    sf::Image img_data;
    if (!img_data.loadFromFile(fileName))
    {
        std::cout << "Error loading image: " << fileName << std::endl;
        return -1;
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    //this->textures.push_back(textureID);

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_data.getSize().x, img_data.getSize().y, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, img_data.getPixelsPtr());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    return textureID;
}

/*void Loader::cleanUp()
{
    // delete VAOs
    for(auto& i : this->vaos)
        glDeleteVertexArrays(1, &i);

    // delete VBOs
    for(auto& i : this->vbos)
        glDeleteBuffers(1, &i);

    // delete Textures
    for(auto& i : this->textures)
        glDeleteTextures(1, &i);
}*/
