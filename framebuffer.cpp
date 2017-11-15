/* 
 * File:   framebuffer.cpp
 * Author: willbroadbelt
 * 
 * Created on 03 November 2017, 17:34
 */

#include "framebuffer.h"
#include "texture.h"

#include <iostream>

Framebuffer::Framebuffer(int width, int height)
{
    Texture texture = Texture(width, height);
    renderedTexture = *texture.getTexture();
    
    m_framebuffer = 0;
    glGenFramebuffers(1, &m_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
    
    //Empty texture;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
     
    glGenRenderbuffers(1, &m_depthrenderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_depthrenderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer(GL_RENDERBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthrenderbuffer);
    
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);

    
    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers);
    
    
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cerr << "Frame buffer failed" << std::endl;
     

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    //glViewport(0,0, width, height);
}

void Framebuffer::Bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
}

void Framebuffer::BindTexture(Texture& tex)
{
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, *tex.getTexture(), 0);
}