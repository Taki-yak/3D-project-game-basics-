#ifndef POINT_H
#define POINT_H

#include <GL/glew.h>
#include <glm/glm.hpp>

class Point {
public:
    Point();                                
    void setPosition(const glm::vec3& position);  
    void setColor(const glm::vec3& color);    
    void draw();                              
    ~Point();                               

private:
    GLuint VAO, VBO[2]; 
};

#endif
