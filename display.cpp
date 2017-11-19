/* 
 * File:   display.cpp
 * Author: willbroadbelt
 * 
 * Created on 30 October 2017, 17:52
 */

#include "display.h"
#include <iostream>
#include <GL/glew.h>
#include <SDL.h>

Display::Display(int width, int height, const std::string& title)
{
    m_width = width;
    m_height = height;
    SDL_Init(SDL_INIT_EVERYTHING);
    
    //Use OpenGL 3.3 - highest supported on MacBookPro mid 2010
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
    
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    
    m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    
    m_glContext = SDL_GL_CreateContext(m_window);
    
    glewExperimental = true;
    GLenum status = glewInit();
    
    if(status != GLEW_OK)
    {
        std::cerr<< "Glew failed to initalise" <<std::endl;
    }
    
    isClosed = false;
    
    glEnable(GL_DEPTH_TEST);
    
    //ISSUE: Doesn't seem to make a difference...
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}
Display::~Display()
{
    SDL_GL_DeleteContext(m_glContext);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Display::Update()
{
    SDL_GL_SwapWindow(m_window);
    
    SDL_Event e;
    
    while(SDL_PollEvent(&e))
    {
        if(e.type == SDL_QUIT)
        {
            isClosed = true;
        }
    }
}

bool Display::IsClosed()
{
    return isClosed;
}

void Display::Clear(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}