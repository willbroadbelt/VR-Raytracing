/* 
 * File:   canvas.cpp
 * Author: willbroadbelt
 * 
 * Created on 21 November 2017, 10:41
 * 
 * Largely taken from OpenGL tutorial 14 - render to texture
 */

#include <vector>
#include <iostream>

#include "canvas.h"
#include "shaderloader.h"


void Canvas::InitQuad() {

    static const GLfloat g_quad_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
    };
    
    glGenVertexArrays(1, &m_vertexArrayObject);
    glBindVertexArray(m_vertexArrayObject);

    glGenBuffers(1, &m_quad_vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_quad_vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof (g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);

    // Create and compile our GLSL program from the shaders
    m_quad_programID = glCreateProgram();
    GLuint quadVertexShader = CreateShader(LoadShader("./Resources/passthrough.vert"), GL_VERTEX_SHADER);
    GLuint quadFragmentShader = CreateShader(LoadShader("./Resources/sdf_ray.frag"), GL_FRAGMENT_SHADER);

    glAttachShader(m_quad_programID, quadVertexShader);
    glAttachShader(m_quad_programID, quadFragmentShader);
    glLinkProgram(m_quad_programID);

    // Check the program
    int InfoLogLength;
    GLint Result = GL_FALSE;
    glGetProgramiv(m_quad_programID, GL_LINK_STATUS, &Result);
    glGetProgramiv(m_quad_programID, GL_INFO_LOG_LENGTH, &InfoLogLength);


    if (InfoLogLength > 0) {
        std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
        glGetProgramInfoLog(m_quad_programID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }


    glDetachShader(m_quad_programID, quadVertexShader);
    glDetachShader(m_quad_programID, quadFragmentShader);

    glDeleteShader(quadVertexShader);
    glDeleteShader(quadFragmentShader);

    //m_texID = glGetUniformLocation(m_quad_programID, "tex");
    //m_timeID = glGetUniformLocation(m_quad_programID, "time");
    this->UniformHandles();
    
    glBindVertexArray(0);
}

void Canvas::DrawCanvas() {
    
    // Render to the screen
    m_fbo.Flush();
    glDisable(GL_DEPTH);

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindVertexArray(m_vertexArrayObject);
    // Use our shader
    glUseProgram(m_quad_programID);

    // Bind our texture in Texture Unit 0
    m_fbo.ActivateTexture();

    // Set our "renderedTexture" sampler to use Texture Unit 0
    //glUniform1i(m_texID, 0);
    //glUniform1f(m_timeID, 1);
    this->UpdateUniforms();

    // 1st attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, m_quad_vertexbuffer);
    glVertexAttribPointer(
            0, // attribute 0. Must match the layout in the shader.
            3, // size
            GL_FLOAT, // type
            GL_FALSE, // normalized?
            0, // stride
            (void*) 0 // array buffer offset
            );
    
    // Draw the triangles !
    glDrawArrays(GL_TRIANGLES, 0, 6); // 2*3 indices starting at 0 -> 2 triangles

    glDisableVertexAttribArray(0);

    m_display.Update();
    glBindVertexArray(0);
}

//Use prior to anything to be rendered to texture.
void Canvas::FBOBind() {
    m_fbo.Bind();
}

void Canvas::PreRender() {
    this->FBOBind();
    m_display.Clear(0.1f, 0.4f, 0.2f, 0.1f);
}

bool Canvas::IsClosed() {
    return m_display.IsClosed();
}

void Canvas::UniformHandles() {
    //m_texID = glGetUniformLocation(m_quad_programID, "tex");
    m_timeID = glGetUniformLocation(m_quad_programID, "currentTime");
    m_resolution = glGetUniformLocation(m_quad_programID, "resolution");
    m_camPos = glGetUniformLocation(m_quad_programID, "camPos");
    m_camDir = glGetUniformLocation(m_quad_programID, "camDir");
    m_camUp = glGetUniformLocation(m_quad_programID, "camUp");
    m_showstepdepth = glGetUniformLocation(m_quad_programID, "showStepDepth");
}

void Canvas::UpdateUniforms() {
    //glUniform1i(m_texID, 0);
    glUniform1f(m_timeID, 1);
    glUniform2f(m_resolution, (GLfloat)m_display.GetWidth(), (GLfloat)m_display.GetHeight());
    glm::vec3 pos = m_camera.GetPos();
    glm::vec3 dir = m_camera.GetDir();
    glm::vec3 up = m_camera.GetUp();
    glUniform3f(m_camPos, (GLfloat)pos.x, (GLfloat)pos.y , (GLfloat)pos.z);
    glUniform3f(m_camDir, (GLfloat)dir.x, (GLfloat)dir.y, (GLfloat)dir.z);
    glUniform3f(m_camUp, (GLfloat)up.x, (GLfloat)up.y, (GLfloat)up.z);
    glUniform1i(m_showstepdepth, (GLuint)0);// 1/0 - T/F
    
}

void Canvas::UpdateCamera(const glm::vec3& pos, const glm::vec3& dir) {
    m_camera.UpdatePos(pos);
    m_camera.UpdateDir(dir);
}
