/* 
 * File:   canvas.h
 * Author: willbroadbelt
 *
 * Created on 21 November 2017, 10:41
 */

#ifndef CANVAS_H
#define CANVAS_H

#include "framebuffer.h"
#include "display.h"

class Canvas
{
public:
    Canvas(int width, int height, const std::string& title = "Window") : 
        m_fbo(width, height), m_display(width, height, title) { InitQuad(); };
    void FBOBind();
    void DrawCanvas();
    void PreRender();
    bool IsClosed();
    
private:
    void InitQuad();
    
    Display m_display;
    Framebuffer m_fbo;
    GLuint m_quad_vertexbuffer, m_quad_programID, m_texID, m_timeID;
};

#endif /* CANVAS_H */
