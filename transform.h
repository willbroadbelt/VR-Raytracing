/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   transform.h
 * Author: willbroadbelt
 *
 * Created on 01 November 2017, 20:35
 */

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm.hpp>
#include <gtx/transform.hpp>

class Transform
{
public:
    Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f)) :
    m_pos(pos),
    m_rot(rot),
    m_scale(scale) {}
    
    inline glm::mat4 GetModel() const
    {
        glm::mat4 posMatrix = glm::translate(m_pos);
        glm::mat4 rotxMatrix = glm::rotate(m_rot.x, glm::vec3(1,0,0));
        glm::mat4 rotyMatrix = glm::rotate(m_rot.y, glm::vec3(0,1,0));
        glm::mat4 rotzMatrix = glm::rotate(m_rot.z, glm::vec3(0,0,1));
        glm::mat4 scaleMatrix = glm::scale(m_scale);
        
        //Rotation in x then y then z.
        glm::mat4 rotMatrix = rotzMatrix * rotyMatrix * rotxMatrix;
        
        //Scale then rotate then position transform.
        return posMatrix * rotMatrix * scaleMatrix;
    }
    
    inline glm::vec3& GetPos() { return m_pos; }
    inline glm::vec3& GetRot() { return m_rot; }
    inline glm::vec3& GetScale() { return m_scale; }
    
    inline void SetPos(const glm::vec3& pos) { m_pos = pos; }
    inline void SetRot(const glm::vec3& rot) { m_rot = rot; }
    inline void SetScale(const glm::vec3& scale) { m_scale = scale; }

    
private:
    glm::vec3 m_pos;
    glm::vec3 m_rot;
    glm::vec3 m_scale;
};


#endif /* TRANSFORM_H */
