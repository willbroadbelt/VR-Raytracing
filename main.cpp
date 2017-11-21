
#include <cstdlib>
#include <iostream>
#include <fstream>
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
#include "shaderloader.h"
#include "canvas.h"

using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;


int main(int argc, char** argv) {
    
    Display display(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL Window");
    Mesh monkey("./Resources/monkey3.obj");
    Texture texture("./Resources/BrickTex.jpg");
    Shader shader("./Resources/basicShader");
    Camera camera(glm::vec3(0,0,-5), 70.0f, (float)(display.GetWidth()/display.GetHeight()), 0.01f, 1000.0f);    
    Canvas canvas(WINDOW_WIDTH, WINDOW_HEIGHT);
    
    Transform transform, transform2;
    float counter = 0.0f;
    
    while(!display.IsClosed())
    {
        //Random transformations for testing.
        float sin = sinf(counter);
        float cos = cosf(counter);
        
        transform.GetPos().z = cos;
        transform.GetRot().x = counter;
        transform.GetRot().y = counter*1.5;
        transform.GetRot().z = counter;
        
        transform2.GetRot().x = counter;
        
        
        //Use FBO with full-screen quad
        canvas.FBOBind();
        display.Clear(0.1f, 0.4f, 0.2f, 0.1f);
        
        shader.Bind();
        texture.Bind(0);
        shader.Update(transform, camera);
        glEnable(GL_DEPTH);
        monkey.Draw();
        
        canvas.DrawCanvas();
        
        display.Update();
        counter += 0.01f;
    }
    
    return 0;
}
