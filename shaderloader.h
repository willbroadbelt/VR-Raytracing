/* 
 * File:   shaderloader.h
 * Author: willbroadbelt
 *
 * Created on 21 November 2017, 10:26
 */

#ifndef SHADERLOADER_H
#define SHADERLOADER_H

#include <GL/glew.h>
#include <string>

void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
GLuint CreateShader(const std::string& text, GLenum shaderType);
std::string LoadShader(const std::string& fileName);

#endif /* SHADERLOADER_H */
