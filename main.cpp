
#include <cstdlib>
#include <iostream>
//#include <OpenGL/gl3.h>
#include <GL/glew.h>
#include <SDL.h>
#include <glm.hpp>

#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"
#include "framebuffer.h"

using namespace std;


int main(int argc, char** argv) {
    //std::cout << glGetString(GL_VERSION)<<std::endl;
    
    Display display(800, 600, "OpenGL Window");
    
    Vertex quadVertices[] = {   Vertex(glm::vec3(-1.0,-1.0,0), glm::vec2(0.0 ,1.0)),
                                Vertex(glm::vec3(1.0,-1.0,0), glm::vec2(0.0, 1.0)),
                                Vertex(glm::vec3(-1.0,1.0,0), glm::vec2(1.0, 0.0)),
                                Vertex(glm::vec3(-1.0,1.0,0), glm::vec2(1.0, 1.0)),
                                Vertex(glm::vec3(1.0,-1.0,0), glm::vec2(1.0, 1.0)),
                                Vertex(glm::vec3(1.0,1.0,0), glm::vec2(1.0, 1.0)),};
    
    unsigned int quadIndices[] = { 0,1,2,1,2,3 };//Two triangles making a quad
    
    Mesh quad(quadVertices, sizeof(quadVertices)/sizeof(quadVertices[0]), quadIndices, sizeof(quadIndices)/sizeof(quadIndices[0]));
    Mesh monkey("./Resources/monkey3.obj");
    Shader shader("./Resources/basicShader");
    //Shader quadShader("./Resources/quadRender");
    Texture texture("./Resources/BrickTex.jpg");
    Transform transform, noTransform;
    Camera camera(glm::vec3(0,0,-5), 70.0f, (float)(display.GetWidth()/display.GetHeight()), 0.01f, 1000.0f);
    //Framebuffer fbo = Framebuffer(800,600); //Errors
    
    float counter = 0.0f;
    
    while(!display.IsClosed())
    {
        display.Clear(0.1f, 0.4f, 0.2f, 0.1f);
        float sin = sinf(counter);
        float cos = cosf(counter);
        
        //transform.GetPos().x = sin;
        transform.GetPos().z = cos;
        transform.GetRot().x = counter;
        transform.GetRot().y = counter*1.5;
        transform.GetRot().z = counter;
        //transform.SetScale(glm::vec3(cos, cos, cos));
        
        shader.Bind();
        texture.Bind(0);
        shader.Update(transform, camera);
        //fbo.Bind();
        //fbo.BindTexture(quad);
        monkey.Draw();
        display.Update();
        counter += 0.01f;
        
        //quadShader.Bind();
        //quadShader.Update(noTransform,camera);
        //quad.Draw();
    }
    
    
    return 0;
}

