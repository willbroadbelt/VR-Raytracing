/* 
 * File:   canvas.h
 * Author: willbroadbelt
 *
 * Created on 21 November 2017, 10:41
 */

#ifndef CANVAS_H
#define CANVAS_H

#include "framebuffer.h"

class Canvas
{
public:
    Canvas(int width, int height) : m_fbo(width, height) { InitQuad(); };
    void FBOBind();
    void DrawCanvas();
    
private:
    void InitQuad();
    
    
    Framebuffer m_fbo;
    GLuint m_quad_vertexbuffer, m_quad_programID, m_texID, m_timeID;
};

#endif /* CANVAS_H */
