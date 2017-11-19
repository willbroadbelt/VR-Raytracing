/* 
 * File:   mesh.h
 * Author: willbroadbelt
 *
 * Created on 31 October 2017, 19:25
 */

#ifndef MESH_H
#define MESH_H

#include<glm.hpp>
#include<GL/glew.h>

#include "obj_loader.h"

class Vertex
{
public:
    Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal = glm::vec3(0,0,0))
    {
        this->pos = pos;
        this->texCoord = texCoord;
        this->normal = normal;
    }
    
    inline glm::vec3* getPos() { return &pos; }
    inline glm::vec2* getTexCoord() { return &texCoord; }
    inline glm::vec3* getNormal() { return &normal; }
    
    
private:
    glm::vec3 pos;//3 GL_FLOATs in a vector
    glm::vec2 texCoord;
    glm::vec3 normal;
    
};

class Mesh
{
public:
    Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
    Mesh(const std::string& fileName);
    void Draw();
    void InitMesh(const IndexedModel& model);
    void DisableMesh();
    
    virtual ~Mesh();
    
    
private:
    
    
    
    enum
    {
        POSITION_VB,
        TEXCOORD_VB,
        NORMAL_VB,
        
        INDEX_VB,
        
        NUM_BUFFERS
    };
    
    GLuint m_vertexArrayObject;
    GLuint m_vertexArrayBuffer[NUM_BUFFERS];
    
    unsigned int m_drawCount;
    
    IndexedModel m_model;
    
};

#endif /* MESH_H */
