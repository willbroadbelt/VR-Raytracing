/* 
 * File:   texture.h
 * Author: willbroadbelt
 *
 * Created on 01 November 2017, 17:56
 */

#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL/glew.h>

class Texture
{
public:
    Texture(const std::string& fileName);
    Texture(int width, int height);
    
    void Bind(unsigned int unit);
    
    inline GLuint* getTexture(){ return &m_texture; }
    
    virtual ~Texture();
    
private:
    GLuint m_texture;    
    
};

#endif /* TEXTURE_H */
