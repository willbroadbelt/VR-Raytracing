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
    void BindTexture(Texture& tex);
    void ActivateTexture();
    
    inline GLuint* getTexture() { return &renderedTexture; }
    inline GLuint* getFB() { return &m_framebuffer; }
    inline GLuint* getDRB() { return &m_depthrenderbuffer; }
    
    virtual ~Framebuffer();
    
private:
    GLuint renderedTexture;
    GLuint m_framebuffer;
    GLuint m_depthrenderbuffer;
    
    int m_width,m_height;
    
};

#endif /* FRAMEBUFFER_H */
