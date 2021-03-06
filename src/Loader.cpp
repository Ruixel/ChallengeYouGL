#include "Loader.h"

std::unique_ptr<RawModel> Loader::loadToVAO(std::vector<GLfloat>& positions, std::vector<GLuint>& indices,
                            std::vector<GLfloat>& texCoords)
{
    GLint vaoID = createVAO();

    // VBOs
    GLuint vboInd  = bindIndicesBuffer(indices);
    GLuint vboVPos = storeDataInAttributeList(0, 3, positions);
    GLuint vboVTex = storeDataInAttributeList(1, 2, texCoords);
    unbindVAO();

    std::cout << "Don't use this please" << std::endl;

    return std::make_unique<RawModel>(vaoID, indices.size(), vboVPos, vboVTex, vboInd);
}

std::unique_ptr<RawModel> Loader::loadToVAO(std::vector<GLfloat>& positions, std::vector<GLuint>& indices,
                            std::vector<GLfloat>& texCoords, std::vector<GLfloat>& normals)
{
    GLint vaoID = createVAO();

    // VBOs
    GLuint vboInd  = bindIndicesBuffer(indices);
    GLuint vboVPos = storeDataInAttributeList(0, 3, positions);
    GLuint vboVTex = storeDataInAttributeList(1, 2, texCoords);
    GLuint vboVNrm = storeDataInAttributeList(2, 3, normals);
    GLuint vboVCol = storeDataInAttributeList(3, 3, positions);
    unbindVAO();

    return std::make_unique<RawModel>(vaoID, indices.size(), vboVPos, vboVTex, vboInd, vboVNrm, vboVCol);
}

std::unique_ptr<RawModel> Loader::loadToVAO(std::vector<GLfloat>& positions, std::vector<GLuint>& indices,
                            std::vector<GLfloat>& texCoords, std::vector<GLfloat>& normals,
                            std::vector<GLfloat>& colors)
{
    GLint vaoID = createVAO();

    // VBOs
    GLuint vboInd  = bindIndicesBuffer(indices);
    GLuint vboVPos = storeDataInAttributeList(0, 3, positions);
    GLuint vboVTex = storeDataInAttributeList(1, 2, texCoords);
    GLuint vboVNrm = storeDataInAttributeList(2, 3, normals);
    GLuint vboVCol = storeDataInAttributeList(3, 3, colors);
    unbindVAO();

    return std::make_unique<RawModel>(vaoID, indices.size(), vboVPos, vboVTex, vboInd, vboVNrm, vboVCol);
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

    img_data.flipVertically();
    img_data.flipHorizontally();

    GLuint textureID;
    glGenTextures(1, &textureID);
    //this->textures.push_back(textureID);

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_data.getSize().x, img_data.getSize().y, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, img_data.getPixelsPtr());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    float aniso = 0.0f;
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);

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
