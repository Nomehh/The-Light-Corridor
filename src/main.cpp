#define GLFW_INCLUDE_NONE
#define _USE_MATH_DEFINES

#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include <GL/gl.h>
#include <iostream>
#include <cmath>
#include <memory>

#define STB_IMAGE_IMPLEMENTATION
#include "../include/3D_tools.hpp"
#include "../include/draw_scene.hpp"
#include "../third_party/stb_image.h"
#include "../include/Racket.hpp"
#include "../include/Ball.hpp"
#include "../include/Wall.hpp"
#include "../include/Level.hpp"

/* Window properties */
static const unsigned int WINDOW_WIDTH = 1920;
static const unsigned int WINDOW_HEIGHT = 1080;
static const char WINDOW_TITLE[] = "The Light Corridor";
static float aspectRatio = 1.0;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 144.;

/* IHM flag */
static int flag_filaire = 0;
static const float GL_VIEW_SIZE = 100.;

/* Ball */
static bool ball_attached = true;
static bool advance = false;

/* Score and life */
unsigned int score = 0;
int life = 5;

/*Button */
int x, y, c;
const auto ball_img = stbi_load("../assets/ballText.jpg", &x, &y, &c, 0);

/* Light */
GLfloat light_position[] = {0., 15.5, 1., 1.0};
GLfloat amb[] = {0.1, 0.1, 0.1, 1.0};
GLfloat diff[] = {200 / 255., 200 / 255., 200 / 255.};
GLfloat spec[] = {75 / 255., 75 / 255, 75 / 255};

/* Position of the choice */
std::unique_ptr<int> choice(new int(2));
std::unique_ptr<double> startPos(new double(3 * M_PI / 2.));
std::unique_ptr<double> targetPos(new double(M_PI / 2.));

std::unique_ptr<float> cursX(new float());
std::unique_ptr<float> cursZ(new float());

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
    setPerspective(60.f, aspectRatio, Z_NEAR, Z_FAR);
    glMatrixMode(GL_MODELVIEW);
}

static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{
    // Convertir les coordonnées de l'écran en coordonnées normalisées
    *cursX = 4 * (-xpos / (WINDOW_WIDTH) + 0.5);
    *cursZ = 2 * (-ypos / (WINDOW_HEIGHT) + 0.5);
}

static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && !ball_attached)
    {
        advance = true;
    }
    else
    {
        advance = false;
    }
}

void drawLife()
{

    glPushMatrix();
    glColor3f(1., 1., 1.);
    glEnable(GL_TEXTURE_2D);
    glScalef(0.05, 0.01, 0.05);
    drawSphere();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void displayLife(int nb_life)
{
    for (int i = 0; i < nb_life; i++)
    {
        glPushMatrix();
        glTranslatef(1.8 - i * 0.2, 13, 0.9);
        drawLife();
        glPopMatrix();
    }
}

void startGame(GLFWwindow *window)
{

    life = 5;

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, ball_img);
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.);

    glLightfv(GL_LIGHT1, GL_AMBIENT, amb);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diff);
    glLightfv(GL_LIGHT1, GL_SPECULAR, spec);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.);

    std::vector<Wall> corridor = Wall::initial_corridor();
    Racket racket;
    Ball ball;
    switch (*choice)
    {
    case 1:
    {
        Level level1 = Level::generate_first_level();
        level1.load_level(corridor);
        break;
    }
    case 3:
    {
        Level::generate_second_level(0).load_level(corridor);
        break;
    }
    case 2:
    {
        Level level1 = Level::generate_first_level();
        level1.load_level(corridor);
        Level::generate_second_level(level1.depth_end_level()).load_level(corridor);
        break;
    }
    }

    Level level1 = Level::generate_first_level();
    level1.load_level(corridor);
    Level::generate_second_level(level1.depth_end_level()).load_level(corridor);

    while (!glfwWindowShouldClose(window))
    { /* Get time (in second) at loop beginning */
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
        setGameCamera();
        glPushMatrix();

        glLightfv(GL_LIGHT0, GL_POSITION, light_position);

        glColor3f(1., 1., 1.);
        glTranslatef(0, 15.5, 0.);
        glScalef(0.1, 0.1, 0.1);
        drawSphere();
        glPopMatrix();

        ball.draw();

        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

        /* Update positions */
        racket.updatePos(*cursX, *cursZ);
        ball.updatePos(*cursX, *cursZ, ball_attached);

        for (auto it = corridor.begin(); it != corridor.end();)
        {
            if ((*it).has_to_be_deleted())
            {
                it = corridor.erase(it);
            }
            else
            {
                it++;
            }
        }

        /* Initial scenery setup */

        racket.check_collision(ball);

        if (advance)
        {
            ball.move(0.05f);
            score++;
        }

        if (ball.lost())
        {
            life--;
            ball_attached = true;
        }

        if (life <= 0)
        {
            std::cout << "You lose :c" << std::endl;
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
        if (score > 2220)
        {
            std::cout << "You win !" << std::endl;
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }

        for (auto &wall : corridor)
        {
            wall.draw();
            wall.ball_collision(ball);
            if (advance)
            {
                wall.advance_wall(0.05f);
            }
        }

        racket.draw();

        glDisable(GL_LIGHTING);

        displayLife(life);

        /* Scene rendering */
        // TODO

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
        {
            *choice = 1;
            *targetPos = M_PI;
        }
        break;
    case GLFW_KEY_W: // z
        if (is_pressed)
        {
            *choice = 2;
            *targetPos = M_PI / 2.;
        }
        break;
    case GLFW_KEY_D:
        if (is_pressed)
        {
            *choice = 3;
            *targetPos = 0;
        }
        break;
    case GLFW_KEY_S:
        if (is_pressed)
        {
            *choice = 0;
            *targetPos = 3 * M_PI / 2.;
        }
        break;
    case GLFW_KEY_ENTER:
        switch (*choice)
        {
        case 0:
            glfwSetWindowShouldClose(window, GLFW_TRUE);
            break;
        case 1:
            startGame(window);
            break;
        case 3:
            startGame(window);
            break;
        case 2:
            startGame(window);
            break;
        default:
            std::cout << "Touche non gérée" << std::endl;
        }
        break; // Add break statement to prevent fall-through
    case GLFW_KEY_V:
        if (is_pressed)
        {
            if (!ball_attached)
                life--;
            ball_attached = !ball_attached;
        }
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

    window = glfwCreateWindow(mode->width, mode->height, "Light Corridor", monitor, NULL);
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
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSwapInterval(1); // synchronisation verticale

    // load triforce
    int x, y, c;
    auto ball_img = stbi_load("../assets/ballText.jpg", &x, &y, &c, 0);

    int x2, y2, c2;
    auto play_img = stbi_load("../assets/play_img.jpg", &x2, &y2, &c2, 0);
    int x3, y3, c3;
    auto quit_img = stbi_load("../assets/quit_img.jpg", &x3, &y3, &c3, 0);

    if (ball_img == nullptr || play_img == nullptr || quit_img == nullptr)
    {
        std::cerr << "Error loading image" << std::endl;
        return -1;
    }

    glEnable(GL_TEXTURE_2D);
    glDisable(GL_TEXTURE_2D);

    GLuint ball_texture = 0;

    glGenTextures(1, &ball_texture);

    glBindTexture(GL_TEXTURE_2D, ball_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, ball_img);

    glPointSize(5.0);
    glEnable(GL_DEPTH_TEST);

    double alpha = 0.;
    double beta = 20;
    double step_alpha = 0.10;
    double step_beta = 0.05;

    // float step_rad = 2 * M_PI / (float)NB_SEG_CIRCLE;
    /* Loop until the user closes the window */
    onWindowResized(window, WINDOW_WIDTH, WINDOW_HEIGHT);
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
        setMenuCamera();

        /* Initial scenery setup */

        glPushMatrix();
        glRotatef(90., 1, 0, 0);
        glRotatef(225., 0, 0, 1);
        {
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
        }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x2, y2, 0, GL_RGB, GL_UNSIGNED_BYTE, play_img);
        drawMenu(alpha, beta, startPos.get(), targetPos.get());
        displayPlayButton();
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x3, y3, 0, GL_RGB, GL_UNSIGNED_BYTE, quit_img);
        displayQuitButton();
        glPopMatrix();

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

    stbi_image_free(ball_img);
    stbi_image_free(play_img);
    stbi_image_free(quit_img);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteTextures(1, &ball_texture);
    glfwTerminate();
    std::cout << "Score : " << score * (life + 1) << std::endl;
    return 0;
}
