
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
    
    Canvas canvas(WINDOW_WIDTH, WINDOW_HEIGHT);
    /*
    Mesh monkey("./Resources/monkey3.obj");
    Texture texture("./Resources/BrickTex.jpg");
    Shader shader("./Resources/basicShader");
    Camera camera(glm::vec3(0,0,-5), 70.0f, (float)(WINDOW_WIDTH/WINDOW_HEIGHT), 0.01f, 1000.0f); 
     
    Transform transform, transform2;
    float counter = 0.0f;
    */
    
    while(!canvas.IsClosed())
    {
        canvas.PreRender();
        canvas.DrawCanvas();
        
        /*
        //Random transformations for testing.
        float sin = sinf(counter);
        float cos = cosf(counter);
        
        transform.GetPos().z = cos;
        transform.GetRot().x = counter;
        transform.GetRot().y = counter*1.5;
        transform.GetRot().z = counter;
        
        transform2.GetRot().x = counter;
        
        
        //Use FBO with full-screen quad
        canvas.PreRender();
        
        //Set up and draw monkey mesh to the canvas FBO
        shader.Bind();
        texture.Bind(0);
        shader.Update(transform, camera);
        monkey.Draw();
        counter += 0.01f;
        
        //Draw canvas FBO to screen
        canvas.DrawCanvas();
        */
    }
    
    return 0;
}
