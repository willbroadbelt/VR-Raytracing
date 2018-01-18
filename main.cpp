
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <time.h>
#include <GL/glew.h>
#include <SDL.h>
#include <glm.hpp>
#include <openvr.h>

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

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;


int main(int argc, char** argv) {
    Canvas canvas(WINDOW_WIDTH, WINDOW_HEIGHT);
    
    float counter = 0.0f,sin, cos;
    
    clock_t t;
    
    while(!canvas.IsClosed())
    {
        t  = clock();
        
        sin = sinf(counter);
        cos = cosf(counter);
        
        //NB: Check if event occurred and only update screen if it has.
        canvas.UpdateCamera(glm::vec3(0,0,8),glm::vec3(sin,0,cos));
        canvas.DrawCanvas();
        
        //Frame rate
        if(clock()-t > 0){
            t = clock() - t;
            printf("Frame rate = %f. Or %d ticks.\n",CLOCKS_PER_SEC/((float)(t)),t);
            t = clock();
        }
        
        counter+=0.02f;
 
    }
    
    return 0;
}
