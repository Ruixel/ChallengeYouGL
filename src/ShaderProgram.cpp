#include "ShaderProgram.h"
#include "GLError.h"

void ShaderProgram::load(const GLchar* vertexPath, const GLchar* fragmentPath)
{
    std::string vertexCode, fragmentCode;
    std::ifstream vShaderFile, fShaderFile;

    vShaderFile.exceptions(std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::badbit);

    try
    {
        // open the files into a buffer
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        // load input buffer into a string buffer
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        // close the files
        vShaderFile.close();
        fShaderFile.close();

        // convert the buffers into a readable string
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();

    } catch (std::ifstream::failure e) {
        // error alert
        std::cout << "Error loading file" << std::endl;
    }

    // variables
    const GLchar* vShaderCode = vertexCode.c_str();
    const GLchar* fShaderCode = fragmentCode.c_str();

    GLuint vertex, fragment;
    GLint success;
    GLchar infolog[512];

    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    this->vertexShaderID = vertex;
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infolog);
        std::cout << "Error loading vertex shader: " << infolog << std::endl;
    }

    // fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    this->fragmentShaderID = fragment;
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infolog);
        std::cout << "Error loading fragment shader: " << infolog << std::endl;
    }

    // compile everything together
    this->programID = glCreateProgram();
    glAttachShader(this->programID, vertex);
    glAttachShader(this->programID, fragment);
    glLinkProgram(this->programID);

    /*glGetProgramiv(this->programID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(this->programID, 512, NULL, infolog);
        std::cout << "Error compiling shader program: " << infolog << std::endl;
    }*/

    glGetProgramiv(this->programID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(this->programID, 512, NULL, infolog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infolog << std::endl;
    }

    // clear what we have
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    //this->getAllUniformLocations();
}

void ShaderProgram::use()
{
    bag::checkForGLerrors();
    glUseProgram(programID);
}

void ShaderProgram::stop()
{
    glUseProgram(0);
}

void ShaderProgram::cleanUp()
{
    glUseProgram(0);
    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragmentShaderID);

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    glDeleteProgram(programID);
}

void ShaderProgram::bindAttribute(GLuint attribute, const GLchar* variableName)
{
    glBindAttribLocation(this->programID, attribute, variableName);
}

////////// UNIFORMS //////////

int ShaderProgram::getUniformLocation(const GLchar* uniformName)
{
    return glGetUniformLocation(this->programID, uniformName);
}

void ShaderProgram::loadFloat(GLuint location, GLfloat value)
{
    glUniform1f(location, value);
}

void ShaderProgram::loadVector(GLuint location, glm::vec3 vector3f)
{
    glUniform3f(location, vector3f.x, vector3f.y, vector3f.z);
}

void ShaderProgram::loadBoolean(GLuint location, bool b)
{
    GLuint val = 0;
    if (b == true)
        val = 1;

    glUniform1i(location, val);
}

void ShaderProgram::loadMatrix(GLuint location, glm::mat4 matrix)
{
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::loadInt(GLuint location, int value)
{
    glUniform1i(location, value);
}
