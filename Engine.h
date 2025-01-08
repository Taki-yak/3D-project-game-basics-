#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <functional>
#include <string>

class Engine {
public:
    Engine(const char* title, int width, int height);  
    GLuint getShaderProgram() const;                  
    void start(const std::function<void()>& render);  
    ~Engine();                                        

private:
    SDL_Window* window;
    SDL_GLContext glContext;
    GLuint shaderProgram;  
    bool isRunning;

    void handleEvents();  
    GLuint compileShaders();  
    void cleanUp();        
};

#endif

