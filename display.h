/* 
 * File:   display.h
 * Author: willbroadbelt
 *
 * Created on 30 October 2017, 17:52
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <SDL.h>

class Display
{
public:
    Display(int width, int height, const std::string& title);
    void Update();
    bool IsClosed();
    void Clear(float r, float g, float b, float a);
    virtual ~Display();
    
    inline float GetWidth(){ return m_width; }
    inline float GetHeight(){ return m_height; }
    
private:
    SDL_Window* m_window;
    SDL_GLContext m_glContext;
    bool isClosed;
    float m_width, m_height;
};

#endif /* DISPLAY_H */
