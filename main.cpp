#include "Engine.h"
#include "Primitive.h"
#include "Cube.h"
#include "Line.h"
#include "Point.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main(int argc, char* argv[]) {
    Engine engine("OpenGL: Cube, Line, and Point", 800, 600);

    GLuint shaderProgram = engine.getShaderProgram();

    Primitive triangle(GL_TRIANGLES);
    triangle.setVertices({
        {0.0f,  0.5f, 0.0f},  
        {-0.5f, -0.5f, 0.0f}, 
        {0.5f, -0.5f, 0.0f}   
        });
    triangle.setColors({
        {1.0f, 0.0f, 0.0f},  
        {0.0f, 1.0f, 0.0f},   
        {0.0f, 0.0f, 1.0f}   
        });

    Cube cube;
    
    Line line;
    line.setEndpoints(glm::vec3(-0.5f, 0.0f, 0.0f), glm::vec3(0.5f, 0.0f, 0.0f));  
    line.setColor(glm::vec3(1.0f, 1.0f, 0.0f)); 

    
    Point point;
    point.setPosition(glm::vec3(-1.0f, 1.0f, 0.0f));  

    point.setColor(glm::vec3(1.0f, 0.0f, 1.0f));     

   
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));  

    engine.start([&]() {
        glUseProgram(shaderProgram);

        GLuint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
        GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        glm::mat4 model = glm::mat4(1.0f);
        GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        triangle.draw();

        model = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f)); 
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        cube.draw();

      
        model = glm::mat4(1.0f);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        line.draw();

        
        glPointSize(6.0f); 
        model = glm::mat4(1.0f);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        point.draw();

        glUseProgram(0);
        });

    return 0;
}
