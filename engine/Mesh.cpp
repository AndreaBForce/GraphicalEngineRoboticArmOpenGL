#include "Mesh.h"

Mesh::Mesh()
{
    //ctor
}

Mesh::~Mesh()
{
    //dtor
}

void Mesh::render(){
// Clear the screen:
    glClearColor(1.0f, 0.6f, 0.1f, 1.0f); // RGBA components
    glClear(GL_COLOR_BUFFER_BIT);

    // Set a matrix to move our triangle:
    glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -45.0f));
    glm::mat4 rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    // Compute model matrix:
    glm::mat4 f = translation * rotationZ;

    glm::mat4 camera = glm::mat4(1.0f);


    // Set model matrix as current OpenGL matrix:
    glLoadMatrixf(glm::value_ptr(f));

    // Pass a triangle (object coordinates: the triangle is centered around the origin):
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-10.0f, -10.0f, 0.0f);
    glVertex3f(10.0f, -10.0f, 0.0f);
    glVertex3f(0.0f, 10.0f, 0.0f);
    glEnd();

    // Swap this context's buffer:
    glutSwapBuffers();
}
