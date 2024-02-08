#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include <vector>
#include <math.h>
#include "../include/Person.hpp"
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <iostream>

/* Window size */
static const unsigned int WINDOW_WIDTH = 1280;
static const unsigned int WINDOW_HEIGHT = 720;
static const unsigned int NB_SEG = 12000;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;

struct Vertex
{
    Vertex(float x, float y) : _x{x}, _y{y}
    {
    }
    float _x;
    float _y;
};
static float aspectRatio;

Person p;

std::vector<Vertex> tableau;
static const float GL_VIEW_SIZE = 6.;

/* Error handling function */
void onError(int error, const char *description)
{
    std::cout << "GLFW Error (" << error << ") : " << description << std::endl;
}

void onWindowResized(GLFWwindow *window, int width, int height)
{
    aspectRatio = width / (float)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (aspectRatio > 1)
    {
        glOrtho(
            -GL_VIEW_SIZE / 2. * aspectRatio, GL_VIEW_SIZE / 2. * aspectRatio,
            -GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2., -1, 1);
    }
    else
    {
        glOrtho(
            -GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.,
            -GL_VIEW_SIZE / 2. / aspectRatio, GL_VIEW_SIZE / 2. / aspectRatio, -1, 1);
    }
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        tableau.emplace_back(x, y);
    }
}

void drawOrigin()
{
    glBegin(GL_LINES);

    glColor3f(1., 0., 0.);

    glVertex2f(-0.5, 0.);
    glVertex2f(0.5, 0.);

    glColor3f(0., 1., 0.);

    glVertex2f(0., 0.5);
    glVertex2f(0., -0.5);

    glEnd();
}

void drawSquare()
{
    glBegin(GL_LINE_LOOP);

    glColor3f(1., 1., 1.);

    glVertex2f(-0.5, 0.);
    glVertex2f(0., 0.5);
    glVertex2f(0.5, 0.);
    glVertex2f(0., -0.5);

    glEnd();
}

void drawCircle()
{
    glBegin(GL_LINE_LOOP);
    glColor3f(0.7, 0, 0.4);
    for (unsigned int i = 0; i < NB_SEG; i++)
    {
        double x = cos(i * 2 * M_PI / (NB_SEG)) / 2;
        double y = sin(i * 2 * M_PI / (NB_SEG)) / 2;
        glVertex2f(x, y);
    }
    glEnd();
}

void drawOrangeCircle()
{
    glBegin(GL_LINE_LOOP);
    glColor3f(1, 0.5, 0.);
    for (unsigned int i = 0; i < NB_SEG; i++)
    {
        double x = cos(i * 2 * M_PI / (NB_SEG)) / 2 + 1;
        double y = sin(i * 2 * M_PI / (NB_SEG)) / 2 + 2;
        glVertex2f(x, y);
    }
    glEnd();
}

int main()
{
    // Initialize the GLFW library
    if (!glfwInit())
    {
        return -1;
    }

    /* Callback to a function if an error is rised by GLFW */
    glfwSetErrorCallback(onError);

    // Create a windowed mode window and its OpenGL context
#ifdef __APPLE__
    // We need to explicitly ask for a 3.3 context on Mac
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGLTemplate", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Intialize glad (loads the OpenGL functions)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return -1;
    }
    onWindowResized(window, WINDOW_WIDTH, WINDOW_HEIGHT);

    glfwSetWindowSizeCallback(window, onWindowResized);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Get time (in second) at loop beginning */
        double startTime = glfwGetTime();

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0, 0.0, 0.0, 0.0);
        drawSquare();
        drawOrigin();
        drawCircle();
        drawOrangeCircle();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        /* Elapsed time computation from loop begining */
        double elapsedTime = glfwGetTime() - startTime;
        /* If to few time is spend vs our wanted FPS, we wait */
        if (elapsedTime < FRAMERATE_IN_SECONDS)
        {
            glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS - elapsedTime);
        }
    }

    glfwTerminate();
    return 0;
}