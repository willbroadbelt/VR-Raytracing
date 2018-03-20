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

#include <fstream>
using namespace std;

class Canvas
{
public:
    Canvas(int width, int height, const std::string& title = "Window") : 
        m_fbo_left(width, height), m_fbo_right(width, height), m_display(width*2, height, title),
        m_camera_left(glm::vec3(0.0f,10.0f,8.0f), glm::vec3(0,0,-1)),
        m_camera_right(glm::vec3(0.0f,10.0f,8.0f), glm::vec3(0,0,-1)) { InitQuad(); 
        m_file.open("results.txt");    };
    void DrawCanvas();
    bool IsClosed();
    void UpdateCamera(const glm::vec3& pos, const glm::vec3& dir);
    ~Canvas(){m_file.close();};
    
private:
    void InitQuad();
    void UpdateUniforms(bool leftEye);
    void UniformHandles();
    
    ofstream m_file;
    Display m_display;
    Framebuffer m_fbo_left,m_fbo_right;
    Camera m_camera_left, m_camera_right;
    GLuint m_quad_vertexbuffer, m_quad_programID, m_vertexArrayObject;
    GLuint m_texID, m_timeID, m_resolution, m_camPos, m_camDir, m_camUp, m_showstepdepth;
};

#endif /* CANVAS_H */
