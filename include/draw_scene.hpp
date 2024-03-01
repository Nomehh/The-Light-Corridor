#pragma once

#define _USE_MATH_DEFINES
#include <GL/gl.h>
#include <iostream>
#include <cmath>
#include <memory>

void drawFrame();

void drawBase();

void drawArm();

void drawPan();

void drawMenu(float alpha, float beta, int *previous_choice, int *choice, double *move_choice);

void first3Circles(float alpha);

void second3Circles(float alpha);

void next2Circles();

void next2CirclesWithDotted(float alpha);

void firstCircleWithPlanet(float alpha);

void secondCircleWithPlanet(float alpha);

void twoDottedSquares();

void mainCircle();

void nextCircleWithPlanet(float angle, float angle2);

void nextMovingDottedCircle(float angle);

void threeOutersCircles(float angle, float angle2);

void displayJouerButton();

void showChoice(int choice, float angle);

void drawChoice(float angle);