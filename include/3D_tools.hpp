#pragma once

#define _USE_MATH_DEFINES
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <iostream>
#include <cmath>

#define NB_SEG_CIRCLE 200

/* Camera parameters and functions */
static const float Z_NEAR = 0.1f;
static const float Z_FAR = 100.f;
extern float theta;     // Angle between x axis and viewpoint
extern float phy;       // Angle between z axis and viewpoint
extern float dist_zoom; // Distance between origin and viewpoint

void setMenuCamera();
void setGameCamera();
void setPerspective(float fovy, float a_ratio, float z_near, float z_far);

/* Draw cannonic objet functions */
void drawSquare();

void drawCircle();

void drawCone();

void drawSphere();

void drawDottedCircle(unsigned int nb_points);

void drawDottedSquare(unsigned int nb_points);

void myDrawCircle();
/* Small tools */
float toRad(float deg);
