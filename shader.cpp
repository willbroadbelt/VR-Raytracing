/* 
 * File:   shader.cpp
 * Author: willbroadbelt
 * 
 * Created on 31 October 2017, 13:52
 */

#include "shader.h"
#include "shaderloader.h"

#include <GL/glew.h>
#include <iostream>
#include <fstream>



Shader::Shader(const std::string& fileName)
{
    m_program = glCreateProgram();
    m_shader[0] = CreateShader(LoadShader(fileName + ".vert"), GL_VERTEX_SHADER);
    m_shader[1] = CreateShader(LoadShader(fileName + ".frag"), GL_FRAGMENT_SHADER);
    
    for(unsigned int i = 0; i < NUM_SHADER; i++)
        glAttachShader(m_program, m_shader[i]);
    
    glBindAttribLocation(m_program, 0, "position");
    glBindAttribLocation(m_program, 1, "texCoord");
    glBindAttribLocation(m_program, 2, "normal");
    
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
//Depreciated...
void Shader::Update(const Transform& transform, const Camera& camera)
{
    //glm::mat4 MVP = camera.getViewProjection() * transform.GetModel();
    //Transpose false
    //glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &MVP[0][0]);
}