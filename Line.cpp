#include "Line.h"

Line::Line() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(2, VBO);  
}

void Line::setEndpoints(const glm::vec3& start, const glm::vec3& end) {
    std::vector<glm::vec3> vertices = { start, end };  

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);  
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

void Line::setColor(const glm::vec3& color) {
    std::vector<glm::vec3> colors = { color, color };  

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr); 
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
}

void Line::draw() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 2);  
    glBindVertexArray(0);
}

Line::~Line() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(2, VBO);
}
