#include "Point.h"

Point::Point() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(2, VBO);  
}

void Point::setPosition(const glm::vec3& position) {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3), &position, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr); 
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

void Point::setColor(const glm::vec3& color) {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3), &color, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr); 
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
}

void Point::draw() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS, 0, 1); 
    glBindVertexArray(0);
}

Point::~Point() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(2, VBO);
}
