/* 
 * File:   camera.h
 * Author: willbroadbelt
 *
 * Created on 02 November 2017, 10:40
 */

#ifndef CAMERA_H
#define CAMERA_H

#include <glm.hpp>
#include <gtx/transform.hpp>

class Camera
{
public:
    Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
    {
        m_perspective = glm::perspective(fov, aspect, zNear, zFar);
        m_position = pos;
        m_forward = glm::vec3(-0.0f,-0.0f,-1.0f);
        m_up = glm::vec3(0.0f,1.0f,0.0f);
    }
    
    inline glm::mat4 getViewProjection() const
    {
        return m_perspective * glm::lookAt(m_position, m_position + m_forward, m_up);
        
    }
    inline glm::vec3 GetPosition() { return m_position; }
    inline glm::vec3 GetUp() { return m_up; }
    inline glm::vec3 GetDir() { return m_forward; }
    
    
private:
    glm::mat4 m_perspective;
    glm::vec3 m_position;
    glm::vec3 m_forward;
    glm::vec3 m_up;
    
    
};

#endif /* CAMERA_H */

