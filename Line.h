#ifndef LINE_H
#define LINE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

class Line {
public:
    Line();                                          
    void setEndpoints(const glm::vec3& start, const glm::vec3& end);  
    void setColor(const glm::vec3& color);           
    void draw();                                 
    ~Line();                                         

private:
    GLuint VAO, VBO[2];  
};

#endif
