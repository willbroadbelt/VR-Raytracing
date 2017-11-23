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
#include "camera.h"

class Canvas
{
public:
    Canvas(int width, int height, const std::string& title = "Window") : 
        m_fbo(width, height), m_display(width, height, title),
        m_camera(glm::vec3(0.0f,0.0f,8.0f), 70.0f, (float)(width/height), 0.01f, 1000.0f) { InitQuad(); };
    void FBOBind();
    void DrawCanvas();
    void PreRender();
    bool IsClosed();
    
private:
    void InitQuad();
    void UpdateUniforms();
    void UniformHandles();
    
    Display m_display;
    Framebuffer m_fbo;
    Camera m_camera;
    GLuint m_quad_vertexbuffer, m_quad_programID, m_vertexArrayObject;
    GLuint m_texID, m_timeID, m_resolution, m_camPos, m_camDir, m_camUp, m_showstepdepth;
};

#endif /* CANVAS_H */
