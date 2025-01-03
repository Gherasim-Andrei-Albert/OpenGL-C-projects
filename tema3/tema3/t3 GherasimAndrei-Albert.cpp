#include <iostream>
#include <glut.h>
#include <math.h>
using namespace std;
// dimensiunea ferestrei in pixeli
#define dim 300


class GrilaCarteziana {
public:
    int nrLinii;
    int nrColoane;
    float gridLineToY(int line) {
        return (float)line / (nrLinii - 1) * 2 - 1;
    }
    float gridColToX(int col) {
        return (float)col / (nrColoane - 1) * 2 - 1;
    }
    void writePixel(int i, int j) {
        float x = gridColToX(i);
        float y = gridLineToY(j);
        glColor3f(0, 0, 1);
        float halfCircleWidth = (float)glutGet(GLUT_WINDOW_WIDTH) / nrColoane / (float)glutGet(GLUT_WINDOW_WIDTH) * 2 /3;
        float halfCircleHeight = (float)glutGet(GLUT_WINDOW_WIDTH) / nrLinii / (float)glutGet(GLUT_WINDOW_WIDTH) * 2 /3;
        /*glPolygonMode(GL_FRONT, GL_FILL);
        glBegin(GL_QUADS);glVertex2f(x- halfCircleWidth,y - halfCircleHeight);
        glVertex2f(x + halfCircleWidth, y - halfCircleHeight);
        glVertex2f(x + halfCircleWidth, y + halfCircleHeight);
        glVertex2f(x - halfCircleWidth, y + halfCircleHeight);
        glEnd();*/
        float XpixelInRelativeUnit = (float)1 / (float)glutGet(GLUT_WINDOW_WIDTH)/2;
        float YpixelInRelativeUnit = (float)1 / (float)glutGet(GLUT_WINDOW_WIDTH)/2;

        float cx = x+XpixelInRelativeUnit/2, cy = y+YpixelInRelativeUnit/2;
        float radius = halfCircleWidth;

        //top
            //decupare in jos
            for (x = cx; x <= cx+halfCircleWidth; x += XpixelInRelativeUnit) {
                //right
                float circleY = cy + sqrt(radius * radius - (x - cx) * (x - cx));
                glBegin(GL_QUADS);
                glVertex2f(x, circleY);
                glVertex2f(x+XpixelInRelativeUnit, circleY);
                glVertex2f(x+XpixelInRelativeUnit, circleY+YpixelInRelativeUnit);
                glVertex2f(x, circleY + YpixelInRelativeUnit);
                glEnd();

                //left
                float opositeX = cx - x;
                circleY = cy + sqrt(radius * radius - (opositeX - cx) * (opositeX - cx));
                glBegin(GL_QUADS);
                glVertex2f(opositeX, circleY);
                glVertex2f(opositeX + XpixelInRelativeUnit, circleY);
                glVertex2f(opositeX + XpixelInRelativeUnit, circleY + YpixelInRelativeUnit);
                glVertex2f(opositeX, circleY + YpixelInRelativeUnit);
                glEnd();
            }
            //decupare la stanga
            for (y = cy; y <= cy+halfCircleHeight; y += YpixelInRelativeUnit) {
                //right
                float circleX = cx + sqrt(radius * radius - (y - cy) * (y - cy));
                glBegin(GL_QUADS);
                glVertex2f(circleX, y);
                glVertex2f(circleX + XpixelInRelativeUnit, y);
                glVertex2f(circleX + XpixelInRelativeUnit, y + YpixelInRelativeUnit);
                glVertex2f(circleX, y + YpixelInRelativeUnit);
                glEnd();

                float x1 = circleX, y1 = y;

                //left
                circleX = cx - sqrt(radius * radius - (y - cy) * (y - cy));
                glBegin(GL_QUADS);
                glVertex2f(circleX, y);
                glVertex2f(circleX + XpixelInRelativeUnit, y);
                glVertex2f(circleX + XpixelInRelativeUnit, y + YpixelInRelativeUnit);
                glVertex2f(circleX, y + YpixelInRelativeUnit);
                glEnd();

                float x2 = circleX, y2 = y+YpixelInRelativeUnit;

                //interior
                glBegin(GL_QUADS);
                glVertex2f(x1, y1);
                glVertex2f(x2, y1);
                glVertex2f(x2, y2);
                glVertex2f(x1, y2);
                glEnd();
            }

        //bottom
            for (x = cx; x <= cx+halfCircleWidth; x += XpixelInRelativeUnit) {
                //right
                float circleY = cy - sqrt(radius * radius - (x - cx) * (x - cx));
                glBegin(GL_QUADS);
                glVertex2f(x, circleY);
                glVertex2f(x + XpixelInRelativeUnit, circleY);
                glVertex2f(x + XpixelInRelativeUnit, circleY + YpixelInRelativeUnit);
                glVertex2f(x, circleY + YpixelInRelativeUnit);
                glEnd();

                //left
                float opositeX = cx - x;
                circleY = cy - sqrt(radius * radius - (opositeX - cx) * (opositeX - cx));
                glBegin(GL_QUADS);
                glVertex2f(opositeX, circleY);
                glVertex2f(opositeX + XpixelInRelativeUnit, circleY);
                glVertex2f(opositeX + XpixelInRelativeUnit, circleY + YpixelInRelativeUnit);
                glVertex2f(opositeX, circleY + YpixelInRelativeUnit);
                glEnd();
            }
            //decupare la stanga
            for (y = cy; y >= cy-halfCircleHeight; y -= YpixelInRelativeUnit) {
                //right
                float circleX = cx + sqrt(radius * radius - (y - cy) * (y - cy));
                glBegin(GL_QUADS);
                glVertex2f(circleX, y);
                glVertex2f(circleX + XpixelInRelativeUnit, y);
                glVertex2f(circleX + XpixelInRelativeUnit, y + YpixelInRelativeUnit);
                glVertex2f(circleX, y + YpixelInRelativeUnit);
                glEnd();

                float x1 = circleX, y1 = y;

                //left
                circleX = cx - sqrt(radius * radius - (y - cy) * (y - cy));
                glBegin(GL_QUADS);
                glVertex2f(circleX, y);
                glVertex2f(circleX + XpixelInRelativeUnit, y);
                glVertex2f(circleX + XpixelInRelativeUnit, y + YpixelInRelativeUnit);
                glVertex2f(circleX, y + YpixelInRelativeUnit);
                glEnd();

                float x2 = circleX, y2 = y + YpixelInRelativeUnit;

                //interior
                glBegin(GL_QUADS);
                glVertex2f(x1, y1);
                glVertex2f(x2, y1);
                glVertex2f(x2, y2);
                glVertex2f(x1, y2);
                glEnd();
            }
    }

    void deseneazaGrila(){
        for (int coloana = 0; coloana < nrColoane; coloana++) {
            glColor3f(0, 0, 0);
            glBegin(GL_LINES); // trasarea unei linii
            glVertex2f((float)coloana / (nrColoane - 1) * 2 - 1, 1);
            glVertex2f((float)coloana / (nrColoane - 1) * 2 - 1, -1);
            glEnd();
        }
        for (int linie = 0; linie < nrLinii; linie++) {
            glColor3f(0, 0, 0);
            glBegin(GL_LINES); // trasarea unei linii
            glVertex2f(-1,(float)linie / (nrLinii - 1) * 2 - 1);
            glVertex2f(1,(float)linie / (nrLinii - 1) * 2 - 1);
            glEnd();
        }
    }
};


void drawLine(float x1, float y1, float x2, float y2, GrilaCarteziana g) {

    glColor3f(1, 0.1, 0.1); // rosu
    glBegin(GL_LINES);
    glVertex2f(g.gridColToX(x1), g.gridLineToY(y1));
    glVertex2f(g.gridColToX(x2), g.gridLineToY(y2));
    glEnd();

    float panta = (y2 - y1) / (x2 - x1);
    float b = y1 - panta * x1;
    for (float x = x1; x <= x2; x++) {
        float y = panta * x + b;
        g.writePixel(x, round(y));
    }
}

void Display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    GrilaCarteziana g;
    g.nrColoane = 16;
    g.nrLinii = 16;
    g.deseneazaGrila();
    drawLine(0, 0, 15, 7, g);
    drawLine(0, 15, 15, 10, g);
    //g.writePixel(1, 14);
    //g.writePixel(7, 7);
    glFlush();
}

void Init(void) {

    glClearColor(1.0, 1.0, 1.0, 1.0);

    glLineWidth(1);

    //   glPointSize(3);

    glPolygonMode(GL_FRONT, GL_LINE);
}

void Reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void MouseFunc(int button, int state, int x, int y) {
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);

    glutInitWindowSize(dim, dim);

    glutInitWindowPosition(100, 100);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutCreateWindow(argv[0]);

    Init();

    glutReshapeFunc(Reshape);

    glutMouseFunc(MouseFunc);

    glutDisplayFunc(Display);

    glutMainLoop();

    return 0;
}