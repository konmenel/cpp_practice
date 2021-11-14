#include <iostream>
#include <vector>
#include "Bodies.h"
#include <GLFW/glfw3.h>

using std::cout;
using std::endl;
using std::string;
using std::vector;

int main()
{
    vector<Body> Masses;

    // Sun
    string name = "Sun";
    vector<double> p(3, 0);
    vector<double> v(3, 0);
    double m = SUN_MASS / EARTH_MASS; // [EARTH MASSES]
    Masses.push_back(Body(p, v, m, name));

    // Earth
    name = "Earth";
    p[0] = 1; // [AU]
    p[2] = 1e6 / AU; // [AU]
    v[1] = 30e3 / AU; // [AU/s]
    m = 1; // [EARTH MASSES]
    Masses.push_back(Body(p, v, m, name));

    // Moon
    name = "Moon";
    p[0] += 384400e3/ AU; // [AU]
    v[1] += -(3683e3/3600) / AU; // [AU/s]
    m = 7.34767309e22 / EARTH_MASS; // [EARTH MASSES]
    Masses.push_back(Body(p, v, m, name));

    for (int n = 0; n<1000000; n++) {
        Masses[1].printPosition();

        forcesSolver(Masses);
        for (uint32_t i = 0; i < Masses.size(); i++) {
            Masses[i].nextInstance();
        }
    }
    
    system("Pause>0");
    return 0;
}

int main_(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(-0.0f,  0.5f);
        glVertex2f( 0.5f, -0.5f);

        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}