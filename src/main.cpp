#define GLFW_INCLUDE_NONE
#define _USE_MATH_DEFINES

#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include <GL/gl.h>
#include <iostream>
#include <cmath>

#include "../include/3D_tools.hpp"
#include "../include/draw_scene.hpp"

/* Window properties */
static const unsigned int WINDOW_WIDTH = 1920;
static const unsigned int WINDOW_HEIGHT = 1080;
static const char WINDOW_TITLE[] = "TD04 Ex01";
static float aspectRatio = 1.0;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 144.;

/* IHM flag */
static int flag_filaire = 0;
static int flag_animate_rot_scale = 0;
static int flag_animate_rot_arm = 0;

std::unique_ptr<int> choice(new int(0));

/* Error handling function */
void onError(int error, const char *description)
{
    std::cout << "GLFW Error (" << error << ") : " << description << std::endl;
}

void onWindowResized(GLFWwindow * /* window */, int width, int height)
{
    aspectRatio = width / (float)height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    setPerspective(60.0, aspectRatio, Z_NEAR, Z_FAR);
    glMatrixMode(GL_MODELVIEW);
}

void onKey(GLFWwindow *window, int key, int /* scancode */, int action, int /* mods */)
{
    int is_pressed = (action == GLFW_PRESS);
    switch (key)
    {

    case GLFW_KEY_ESCAPE:
        if (is_pressed)
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        break;
    case GLFW_KEY_F:
        if (is_pressed)
        {
            flag_filaire = !flag_filaire;
            std::cout << "Mode filaire : " << ((flag_filaire) ? "ON" : "OFF") << std::endl;
        }
        break;
    case GLFW_KEY_A: // q
        if (is_pressed)
            *choice = 1;
        break;
    case GLFW_KEY_W: // z
        if (is_pressed)
            *choice = 2;
        break;
    case GLFW_KEY_D:
        if (is_pressed)
            *choice = 3;
        break;
    case GLFW_KEY_S:
        if (is_pressed)
            *choice = 0;
        break;
    case GLFW_KEY_R:
        if (is_pressed)
            flag_animate_rot_arm = 1 - flag_animate_rot_arm;
        break;
    case GLFW_KEY_T:
        if (is_pressed)
            flag_animate_rot_scale = 1 - flag_animate_rot_scale;
        break;
    case GLFW_KEY_J:
        if (dist_zoom < 60.0f)
            dist_zoom *= 1.1;
        std::cout << "Zoom is " << dist_zoom << std::endl;
        break;
    case GLFW_KEY_I:
        if (dist_zoom > 1.0f)
            dist_zoom *= 0.9;
        std::cout << "Zoom is " << dist_zoom << std::endl;
        break;
    case GLFW_KEY_UP:
        if (phy > 2)
            phy -= 2;
        std::cout << "Phy : " << phy << std::endl;
        break;
    case GLFW_KEY_DOWN:
        if (phy <= 88.)
            phy += 2;
        std::cout << "Phy : " << phy << std::endl;
        break;
    case GLFW_KEY_LEFT:
        theta -= 5;
        break;
    case GLFW_KEY_RIGHT:
        theta += 5;
        break;
    default:
        std::cout << "Touche non gérée" << std::endl;
    }
}

int main(int /* argc */, char ** /* argv */)
{
    /* GLFW initialisation */
    GLFWwindow *window;
    if (!glfwInit())
        return -1;

    /* Callback to a function if an error is rised by GLFW */
    glfwSetErrorCallback(onError);

    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);

    // glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    // glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    // glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    window = glfwCreateWindow(mode->width, mode->height, "My Title", monitor, NULL);
    glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);

    std::cout << "Width : " << mode->width << " Height : " << mode->height << " Framerate : " << mode->refreshRate << std::endl;

    /* Create a windowed mode window and its OpenGL context */

    if (!window)
    {
        // If no context created : exit !
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */

    glfwMakeContextCurrent(window);

    // Intialize glad (loads the OpenGL functions)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return -1;
    }

    glfwSetWindowSizeCallback(window, onWindowResized);
    glfwSetKeyCallback(window, onKey);
    glfwSwapInterval(1); // synchronisation verticale

    onWindowResized(window, WINDOW_WIDTH, WINDOW_HEIGHT);

    glPointSize(5.0);
    glEnable(GL_DEPTH_TEST);

    double alpha = 0.;
    double beta = 20;
    double step_alpha = 0.10;
    double step_beta = 0.05;
    std::unique_ptr<int> previous_choice(new int(0));
    std::unique_ptr<double> move_choice(new double(45.));
    // float step_rad = 2 * M_PI / (float)NB_SEG_CIRCLE;
    /* Loop until the user closes the window */

    while (!glfwWindowShouldClose(window))
    {
        /* Get time (in second) at loop beginning */
        double startTime = glfwGetTime();

        /* Cleaning buffers and setting Matrix Mode */
        glClearColor(0.2, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (flag_filaire)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        setCamera();

        /* Initial scenery setup */
        glPushMatrix();
        glTranslatef(0.0, 0.0, -0.01);
        glScalef(100.0, 100.0, 1.0);
        glColor3f(0.0, 0.0, 0.);
        drawSquare();
        glBegin(GL_POINTS);
        glColor3f(1.0, 1.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glEnd();
        glPopMatrix();

        // drawDottedCircle();
        // drawDottedSquare();

        drawMenu(alpha, beta, previous_choice.get(), choice.get(), move_choice.get());

        /* Scene rendering */
        // drawFrame();
        // glPushMatrix();
        // {
        // 	glRotatef(alpha++, 0, 0, 1);
        // 	drawBase();

        // 	glPushMatrix();
        // 	{
        // 		glTranslatef(0, 0, 10);
        // 		drawArm();
        // 	}

        // 	glPopMatrix();

        // 	glPushMatrix();
        // 	{
        // 		glColor3f(1, 0.0, 0);
        // 		glTranslatef(2 * cos(i * step_rad), 2 * sin(i * step_rad), 5);
        // 		drawSphere();
        // 		i++;
        // 	}
        // 	glPopMatrix();

        // 	glPushMatrix();
        // 	{

        // 		glTranslatef(0, 10, 10);
        // 		glRotatef(beta, 0, 1, 0);
        // 		drawPan();
        // 	}
        // 	glPopMatrix();
        // 	glPushMatrix();
        // 	{
        // 		glTranslatef(0, -10, 10);
        // 		glRotatef(delta, 0, 1, 0);
        // 		drawPan();
        // 	}
        // }
        // glPopMatrix();
        // glPopMatrix();

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

        /* Animate scenery */

        alpha += step_alpha;
        beta += step_beta;
    }

    glfwTerminate();
    return 0;
}
