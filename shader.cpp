/* 
 * File:   shader.cpp
 * Author: willbroadbelt
 * 
 * Created on 31 October 2017, 13:52
 */

#include "shader.h"
#include <GL/glew.h>
#include <iostream>
#include <fstream>



Shader::Shader(const std::string& fileName)
{
    m_program = glCreateProgram();
    m_shader[0] = CreateShader(LoadShader(fileName + ".vertexshader"), GL_VERTEX_SHADER);
    m_shader[1] = CreateShader(LoadShader(fileName + ".fragmentshader"), GL_FRAGMENT_SHADER);
    
    for(unsigned int i = 0; i < NUM_SHADER; i++)
        glAttachShader(m_program, m_shader[i]);
    
    glBindAttribLocation(m_program, 0, "position");
    glBindAttribLocation(m_program, 1, "texCoord");
    glBindAttribLocation(m_program, 2, "normal");
    
    //GLuint TextureID  = glGetUniformLocation(programID, "myTextureSampler");
    
    glLinkProgram(m_program);
    CheckShaderError(m_program, GL_LINK_STATUS, true, "Err: Shader failed to link.");
    
    glValidateProgram(m_program);
    CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Err: Shader is invalid.");
    
    m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
}

Shader::~Shader()
{
    for(unsigned int i = 0; i < NUM_SHADER; i++)
    {
        glDetachShader(m_program, m_shader[i]);
        glDeleteShader(m_shader[i]);
    }
    
    
    glDeleteProgram(m_program);
}

void Shader::Bind()
{
    glUseProgram(m_program);
}

void Shader::Update(const Transform& transform, const Camera& camera)
{
    glm::mat4 MVP = camera.getViewProjection() * transform.GetModel();
    //Transpose false
    glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &MVP[0][0]);
}

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
    GLint success = 0;
    GLchar error[1024] = { 0 };

    if(isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);

    if(success == GL_FALSE)
    {
        if(isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);

        std::cerr << errorMessage << ": '" << error << "'" << std::endl;
    }
}

GLuint Shader::CreateShader(const std::string& text, GLenum shaderType)
{
    GLuint shader = glCreateShader(shaderType);
    
    if(shader==0)
        std::cerr<< "Shader creation failed" << std::endl;
    
    const GLchar* shaderSourceStrings[1];
    GLint shaderSourceStringLengths[1];
    
    shaderSourceStrings[0] = text.c_str();
    shaderSourceStringLengths[0] = text.length();
    
    glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
    glCompileShader(shader);
    
    CheckShaderError(shader, GL_COMPILE_STATUS, false, "Err: Shader failed to compile.");

    
    return shader;
    
}

std::string Shader::LoadShader(const std::string& fileName)
{
    std::ifstream file;
    file.open((fileName).c_str());

    std::string output;
    std::string line;

    if(file.is_open())
    {
        while(file.good())
        {
            getline(file, line);
			output.append(line + "\n");
        }
    }
    else
    {
		std::cerr << "Unable to load shader: " << fileName << std::endl;
    }

    return output;
}

