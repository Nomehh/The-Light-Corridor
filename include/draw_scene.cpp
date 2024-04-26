#include "draw_scene.hpp"
#include "3D_tools.hpp"

void drawFrame()
{
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);
    glEnd();
}

void drawBase()
{
    glPushMatrix();
    {
        // on dessine la base du cercle
        glScalef(1.5, 1.5, 0);
        glColor3f(235 / 255., 207 / 255., 52 / 255.);
        drawCircle();
    }
    glPopMatrix();

    glPushMatrix();
    {
        // on dessine la base du cercle
        glScalef(1, 1, 10);
        glColor3f(235 / 255., 207 / 255., 52 / 255.);
        drawCone();
    }
    glPopMatrix();
}

void drawArm()
{
    glColor3f(245 / 255., 164 / 255., 66 / 255.);
    glPushMatrix();
    {
        // on dessine la sphere
        glScalef(1.6, 1.6, 1.6);

        drawSphere();
    }
    glPopMatrix();

    glPushMatrix();
    {
        // on dessine le bras 1
        glRotatef(90, 1, 0, 0);
        glScalef(1, 1, 10);
        drawCone();
    }
    glPopMatrix();
    glPushMatrix();
    {
        // on dessine le bras 2
        glRotatef(-90, 1, 0, 0);
        glScalef(1, 1, 10);
        drawCone();
    }
    glPopMatrix();
}

void drawPan()
{

    glPushMatrix();
    {
        glColor3f(89 / 255., 115 / 255., 0.);
        glTranslatef(0, 0, -5);
        glScalef(3, 3, 0);
        drawCircle();
    }
    glPopMatrix();

    glPushMatrix();
    {
        glScalef(3, 3, -5);
        glBegin(GL_LINES);
        glColor3f(1., 0., 0.);
        glVertex3f(0, 0, 0);
        glVertex3f(cos(2 * M_PI / 3.), sin(2 * M_PI / 3.), 1.);
        glVertex3f(0, 0, 0);
        glVertex3f(cos(4 * M_PI / 3.), sin(4 * M_PI / 3.), 1.);
        glVertex3f(0, 0, 0);
        glVertex3f(cos(6 * M_PI / 3.), sin(6 * M_PI / 3.), 1.);
        glEnd();
    }
    glPopMatrix();
}

double findShortestPath(double startPos, double targetPos)
{
    double moveTrigo = fmod(targetPos - startPos + 2 * M_PI, 2 * M_PI);
    double moveClockwise = fmod(startPos - targetPos + 2 * M_PI, 2 * M_PI);

    if (moveTrigo < moveClockwise)
    {

        return moveTrigo;
    }
    else
    {

        return -moveClockwise;
    }
}

void drawMenu(float alpha, float beta, double *startPos, double *targetPos)
{

    double path = findShortestPath(*startPos, *targetPos);

    path /= 80;
    *startPos += path;

    showChoice(*startPos, -alpha - beta);
    first3Circles(alpha);
    second3Circles(-alpha);
    next2Circles();
    next2CirclesWithDotted(alpha);
    firstCircleWithPlanet(-alpha);
    secondCircleWithPlanet(-beta);
    twoDottedSquares();
    mainCircle();
    nextCircleWithPlanet(-alpha, beta);
    nextMovingDottedCircle(beta);
    threeOutersCircles(alpha, -alpha);
    displayJouerButton();
}

void first3Circles(float alpha)
{
    glPushMatrix();
    {
        glColor3f(1., 1., 1.);
        glRotatef(alpha, 0, 0, 1);
        glScalef(0.4, 0.4, 0);
        drawDottedCircle(30);
        glPushMatrix();
        {
            glScalef(0.8, 0.8, 0.);
            myDrawCircle();
            glPushMatrix();
            {
                glScalef(0.84, 0.84, 0.);
                myDrawCircle();
            }
            glPopMatrix();
        }
        glPopMatrix();
    }
    glPopMatrix();
}

void second3Circles(float alpha)
{
    glPushMatrix();
    {
        glColor3f(1., 1., 1.);
        glRotatef(alpha, 0, 0, 1);
        glScalef(0.8, 0.8, 0);
        drawDottedCircle(40);
        glPushMatrix();
        {
            glScalef(0.9, 0.9, 0.);
            myDrawCircle();
            glPushMatrix();
            {
                glScalef(0.84, 0.84, 0.);
                myDrawCircle();
            }
            glPopMatrix();
        }
        glPopMatrix();
    }
    glPopMatrix();
}

void next2Circles()
{
    glPushMatrix();
    {
        glColor3f(1., 1., 1.);
        glScalef(2, 2, 0);
        myDrawCircle();
        glPushMatrix();
        {
            glScalef(0.9, 0.9, 0);
            myDrawCircle();
        }
        glPopMatrix();
    }
    glPopMatrix();
}

void next2CirclesWithDotted(float alpha)
{
    glPushMatrix();
    {
        glColor3f(1., 1., 1.);
        glScalef(2.9, 2.9, 0);
        myDrawCircle();
        glPushMatrix();
        {
            glRotatef(alpha, 0, 0, 1);
            glScalef(0.95, 0.95, 0);
            drawDottedCircle(200);
        }
        glPopMatrix();
    }
    glPopMatrix();
}

void firstCircleWithPlanet(float alpha)
{
    glPushMatrix();
    {
        glColor3f(1., 1., 1.);
        glScalef(3.2, 3.2, 0);
        myDrawCircle();
        glPushMatrix();
        {
            glTranslatef(cos(alpha * M_PI / 180), sin(alpha * M_PI / 180), 0);
            glPushMatrix();
            {
                glScalef(0.06, 0.06, 0);
                myDrawCircle();
            }
            glPopMatrix();
            glScalef(0.029, 0.029, 0);
            drawCircle();
        }
        glPopMatrix();
    }
    glPopMatrix();
}

void secondCircleWithPlanet(float alpha)
{
    glPushMatrix();
    {
        glScalef(4.3, 4.3, 0);
        glPushMatrix();
        {
            glColor3f(1., 1., 1.);
            glTranslatef(cos(alpha * M_PI / 180), sin(alpha * M_PI / 180), 0);
            glPushMatrix();
            {
                // planet
                glScalef(0.01, 0.01, 0);
                drawCircle();
            }
            glPopMatrix();
            glPushMatrix();
            {
                // first orbit
                glScalef(0.035, 0.035, 0);
                myDrawCircle();
            }
            glPopMatrix();
            glPushMatrix();
            {
                // second orbit
                glScalef(0.045, 0.045, 0);
                myDrawCircle();
            }
            glPopMatrix();
        }
        glPopMatrix();
        glColor3f(0.6, 0.6, 0.6);
        // big orbit in gray
        myDrawCircle();
    }
    glPopMatrix();
}

void twoDottedSquares()
{
    glPushMatrix();
    {
        glColor3f(0.6, 0.6, 0.6);
        glScalef(7.2, 7.2, 0);
        drawDottedSquare(80);
    }
    glPopMatrix();
    glPushMatrix();
    {
        glColor3f(0.6, 0.6, 0.6);
        glScalef(7.2, 7.2, 0);
        glRotatef(45, 0, 0, 1);
        drawDottedSquare(80);
    }
    glPopMatrix();
}

void mainCircle()
{
    glPushMatrix();
    {

        glColor3f(1., 1., 1.);
        glScalef(5.13, 5.13, 0);
        glLineWidth(4.);
        myDrawCircle();
        glLineWidth(1.);
    }
    glPopMatrix();
}

void nextCircleWithPlanet(float angle, float angle2)
{
    glPushMatrix();
    {
        glColor3f(1., 1., 1.);
        glScalef(11, 11, 0);
        glLineWidth(3.);
        myDrawCircle();
        glLineWidth(1.);
        glPushMatrix();
        {
            glTranslatef(cos(angle * M_PI / 180), sin(angle * M_PI / 180), 0);
            glPushMatrix();
            {
                glScalef(0.065, 0.065, 0);
                myDrawCircle();
                glPushMatrix();
                {
                    glTranslatef(cos(angle2 * M_PI / 180), sin(angle2 * M_PI / 180), 0);
                    glScalef(0.1, 0.1, 0);
                    drawCircle();
                }
                glPopMatrix();
                glPushMatrix();
                {
                    glScalef(0.7, 0.7, 0);
                    myDrawCircle();
                }
                glPopMatrix();
                glPushMatrix();
                {
                    glScalef(0.6, 0.6, 0);
                    myDrawCircle();
                }
                glPopMatrix();
            }
            glPopMatrix();
            glScalef(0.025, 0.025, 0);
            drawCircle();
        }
        glPopMatrix();
    }
    glPopMatrix();
}

void nextMovingDottedCircle(float angle)
{
    glPushMatrix();
    {
        glColor3f(0.6, 0.6, 0.6);
        glScalef(12, 12, 0);
        glPushMatrix();
        {
            glRotatef(angle, 0, 0, 1);
            drawDottedCircle(400);
        }
        glPopMatrix();
    }
    glPopMatrix();
}

void threeOutersCircles(float angle, float angle2)
{
    glPushMatrix();
    {
        glColor3f(1., 1., 1.);
        glScalef(14.8, 14.8, 0);
        myDrawCircle();
        glPushMatrix();
        { // planet on the outer orbit
            glTranslatef(cos(-angle / 2 * M_PI / 180), sin(-angle / 2 * M_PI / 180), 0);
            glPushMatrix();
            {
                glScalef(0.04, 0.04, 0);
                glPushMatrix();
                { // plenty orbit
                    glScalef(0.8, 0.8, 0);
                    myDrawCircle();
                    glPushMatrix();
                    { // planet on plenty orbit
                        glTranslatef(cos(angle * 1.3 * M_PI / 180), sin(angle * 1.3 * M_PI / 180), 0);
                        glScalef(0.1, 0.1, 0);
                        drawCircle();
                        glPushMatrix();
                        { // plenty orbit on the lil planet
                            glScalef(2.8, 2.8, 0);
                            myDrawCircle();
                        }
                        glPopMatrix();
                    }
                    glPopMatrix();
                }
                glPopMatrix();
                glPushMatrix();
                { // dotted orbit
                    glRotatef(angle2, 0, 0, 1);
                    glScalef(0.3, 0.3, 0);
                    drawDottedCircle(15);
                }
                glPopMatrix();
            }
            glPopMatrix();
            glScalef(0.01, 0.01, 0);
            drawCircle(); // draw the planet
        }
        glPopMatrix();
        glPushMatrix();
        {
            glPushMatrix();
            {
                glScalef(0.92, 0.92, 0);
                glLineWidth(4.);
                myDrawCircle();
                glLineWidth(1.);
                glPushMatrix();
                { // planet on the thick orbit
                    glTranslatef(cos(angle * M_PI / 180), sin(angle * M_PI / 180), 0);
                    glPushMatrix();
                    {
                        glScalef(0.03, 0.03, 0);
                        glPushMatrix();
                        { // plenty orbit
                            glScalef(0.7, 0.7, 0);
                            myDrawCircle();
                        }
                        glPopMatrix();
                        glPushMatrix();
                        { // plenty orbit
                            glScalef(0.6, 0.6, 0);
                            myDrawCircle();
                        }
                        glPopMatrix();
                        glPushMatrix();
                        { // dotted orbit
                            glRotatef(angle2, 0, 0, 1);
                            glScalef(0.8, 0.8, 0);
                            drawDottedCircle(20);
                        }
                        glPopMatrix();
                    }
                    glPopMatrix();
                    glScalef(0.008, 0.008, 0);
                    drawCircle();
                }
                glPopMatrix();
            }
            glPopMatrix();
            myDrawCircle();
            glPushMatrix();
            { // draw inner orbit of the three.
                glScalef(0.9, 0.9, 0);
                myDrawCircle();
            }
            glPopMatrix();
        }
        glPopMatrix();
    }
    glPopMatrix();
}

void displayJouerButton()
{
    // Activer la texture
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    {
        glBegin(GL_QUADS);
        // Associer les coordonnées de texture aux sommets
        glTexCoord2f(0.0, 1.0); // Coin inférieur gauche (inversé verticalement)
        glVertex3f(-1.0, -1.0, 0.0);

        glTexCoord2f(1.0, 1.0); // Coin inférieur droit (inversé verticalement)
        glVertex3f(1.0, -1.0, 0.0);

        glTexCoord2f(1.0, 0.0); // Coin supérieur droit (inversé verticalement)
        glVertex3f(1.0, 1.0, 0.0);

        glTexCoord2f(0.0, 0.0); // Coin supérieur gauche (inversé verticalement)
        glVertex3f(-1.0, 1.0, 0.0);
        glEnd();
    }
    glPopMatrix();

    // Désactiver la texture
    glDisable(GL_TEXTURE_2D);
}

void showChoice(double pos, float angle)
{

    glPushMatrix();
    {
        // translate to the right position with radiant
        glRotatef(135, 0, 0, 1);
        glTranslatef(5.13 * cos(pos), 5.13 * sin(pos), 0);
        glScalef(0.3, 0.3, 0.3);
        drawChoice(angle);
    }
    glPopMatrix();
}

void drawChoice(float angle)
{
    glPushMatrix();
    { // plenty circle
        glColor3f(1., 1., 1.);
        glScalef(0.7, 0.7, 0);
        drawCircle();
    }
    glPopMatrix();
    glPushMatrix();
    { // plenty orbit
        glColor3f(1., 1., 1.);
        glScalef(1.2, 1.2, 0);
        myDrawCircle();
    }
    glPopMatrix();
    glPushMatrix();
    { // plenty orbit
        glColor3f(1., 1., 1.);
        glScalef(1.4, 1.4, 0);
        myDrawCircle();
    }
    glPopMatrix();
    glPushMatrix();
    { // plenty orbit
        glColor3f(1., 1., 1.);
        glScalef(1.6, 1.6, 0);
        myDrawCircle();
    }
    glPopMatrix();
    glPushMatrix();
    {
        glColor3f(1., 1., 1.);
        glScalef(1.8, 1.8, 0);
        myDrawCircle();
    }
    glPopMatrix();
    glPushMatrix();
    {
        glRotatef(angle, 0, 0, 1);
        glColor3f(1., 1., 1.);
        glScalef(2, 2, 0);
        drawDottedCircle(40);
    }
    glPopMatrix();
}