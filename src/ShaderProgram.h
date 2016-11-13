#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class ShaderProgram
{
protected:
    void bindAttribute(GLuint attribute, const GLchar* variableName);
    int getUniformLocation(const GLchar* uniformName);

    void loadFloat(GLuint location, GLfloat value);
    void loadVector(GLuint location, glm::vec3 vector3f);
    void loadBoolean(GLuint location, bool b);
    void loadMatrix(GLuint location, glm::mat4 matrix4f);

private:
    GLuint programID;
    int vertexShaderID;
    int fragmentShaderID;

    virtual void bindAttributes() = 0;
    virtual void getAllUniformLocations() = 0;

public:
    void load(const GLchar* vertexPath, const GLchar* fragmentPath);
    GLuint getProgramId() { return this->programID; }

    virtual void loadProjectionMatrix(const glm::mat4& matrix) = 0;

    void use();
    void stop();
    void cleanUp();
};

#endif // SHADERPROGRAM_H
