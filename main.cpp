
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

using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;


//TODO: Move to separate class/refactor code from main for the quad
void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
    GLint success = 0;
    GLchar error[1024] = { 0 };

    if(isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);

    if(success == GL_FALSE)
    {
        if(isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);

        std::cerr << errorMessage << ": '" << error << "'" << std::endl;
    }
}

GLuint CreateShader(const std::string& text, GLenum shaderType)
{
    GLuint shader = glCreateShader(shaderType);
    
    if(shader==0)
        std::cerr<< "Shader creation failed" << std::endl;
    
    const GLchar* shaderSourceStrings[1];
    GLint shaderSourceStringLengths[1];
    
    shaderSourceStrings[0] = text.c_str();
    shaderSourceStringLengths[0] = text.length();
    
    glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
    glCompileShader(shader);
    
    CheckShaderError(shader, GL_COMPILE_STATUS, false, "Err: Shader failed to compile.");

    
    return shader;
    
}

std::string LoadShader(const std::string& fileName)
{
    std::ifstream file;
    file.open((fileName).c_str());

    std::string output;
    std::string line;

    if(file.is_open())
    {
        while(file.good())
        {
            getline(file, line);
			output.append(line + "\n");
        }
    }
    else
    {
		std::cerr << "Unable to load shader: " << fileName << std::endl;
    }

    return output;
}



int main(int argc, char** argv) {
    
    Display display(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL Window");
    Mesh monkey("./Resources/monkey3.obj");
    Texture texture("./Resources/BrickTex.jpg");
    Shader shader("./Resources/basicShader");
    
    Transform transform, transform2;
    
    Camera camera(glm::vec3(0,0,-5), 70.0f, (float)(display.GetWidth()/display.GetHeight()), 0.01f, 1000.0f);
    Framebuffer fbo = Framebuffer(WINDOW_WIDTH,WINDOW_HEIGHT);
    
    float counter = 0.0f;
    
    //Framebuffer quad setup - move to separate class
    static const GLfloat g_quad_vertex_buffer_data[] = { 
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,
	};

	GLuint quad_vertexbuffer;
	glGenBuffers(1, &quad_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);

	// Create and compile our GLSL program from the shaders
	GLuint quad_programID = glCreateProgram();
        GLuint quadVertexShader = CreateShader(LoadShader("./Resources/quadRender.vertexshader"), GL_VERTEX_SHADER);
        GLuint quadFragmentShader = CreateShader(LoadShader("./Resources/quadRender.fragmentshader"), GL_FRAGMENT_SHADER);
        
        glAttachShader(quad_programID, quadVertexShader);
	glAttachShader(quad_programID, quadFragmentShader);
	glLinkProgram(quad_programID);

	// Check the program
        int InfoLogLength;
        GLint Result = GL_FALSE;
	glGetProgramiv(quad_programID, GL_LINK_STATUS, &Result);
	glGetProgramiv(quad_programID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        
        
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(quad_programID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	
	glDetachShader(quad_programID, quadVertexShader);
	glDetachShader(quad_programID, quadFragmentShader);
	
	glDeleteShader(quadVertexShader);
	glDeleteShader(quadFragmentShader);
        
	GLuint texID = glGetUniformLocation(quad_programID, "renderedTexture");
	GLuint timeID = glGetUniformLocation(quad_programID, "time");
    
    
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
        fbo.Bind();
        display.Clear(0.1f, 0.4f, 0.2f, 0.1f);
        
        shader.Bind();
        texture.Bind(0);
        shader.Update(transform, camera);
        glEnable(GL_DEPTH);
        monkey.Draw();
        
        // Render to the screen
        fbo.Flush();
        glDisable(GL_DEPTH);
        
	// Clear the screen
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Use our shader
	glUseProgram(quad_programID);

	// Bind our texture in Texture Unit 0
        fbo.ActivateTexture();
                
	// Set our "renderedTexture" sampler to use Texture Unit 0
	glUniform1i(texID, 0);

	glUniform1f(timeID, 1 );

	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	// Draw the triangles !
	glDrawArrays(GL_TRIANGLES, 0, 6); // 2*3 indices starting at 0 -> 2 triangles

	glDisableVertexAttribArray(0);
        display.Update();
        counter += 0.01f;
    }
    
    return 0;
}
