/* 
 * File:   framebuffer.h
 * Author: willbroadbelt
 *
 * Created on 03 November 2017, 17:34
 */

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include <GL/glew.h>
#include "texture.h"

class Framebuffer
{
public:
    Framebuffer(int width, int height);
    void Bind();
    void Flush();
    void ActivateTexture();

    virtual ~Framebuffer();
    
private:
    GLuint m_renderedTexture;
    GLuint m_framebuffer;
    GLuint m_depthrenderbuffer;
    
    int m_width,m_height;
    
};

#endif /* FRAMEBUFFER_H */
