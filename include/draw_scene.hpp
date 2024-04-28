#pragma once

#define _USE_MATH_DEFINES
#include <GL/gl.h>
#include <iostream>
#include <cmath>
#include <memory>

void drawFrame();

void drawMenu(float alpha, float beta, double *move_choice, double *last_move);

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

void showChoice(double pos, float angle);

void drawChoice(float angle);

double findShortestPath(double startPos, double targetPos);