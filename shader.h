/* 
 * File:   shader.h
 * Author: willbroadbelt
 *
 * Created on 31 October 2017, 13:52
 */

#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>
#include <OpenGL/gl.h>

#include "transform.h"
#include "camera.h"
//#include <SDL.h>

class Shader
{
public:
    Shader(const std::string& fileName);
    
    void Bind();
    void Update(const Transform& transform, const Camera& camera);
    
    virtual ~Shader();
    
private:
    static const unsigned int NUM_SHADER = 2;
    
    void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
    std::string LoadShader(const std::string& fileName);
    GLuint CreateShader(const std::string& text, GLenum shaderType);
    
    enum{
        TRANSFORM_U,
        
        NUM_UNIFORMS
    };
    
    GLuint m_program;
    GLuint m_shader[NUM_SHADER];
    GLuint m_uniforms[NUM_UNIFORMS];
};

#endif /* SHADER_H */
