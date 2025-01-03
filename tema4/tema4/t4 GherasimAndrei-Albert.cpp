#include <iostream>
#include <glut.h>
#include <math.h>
#include <vector>
using namespace std;
// dimensiunea ferestrei in pixeli
#define dim 300


const double PI = asin(1) * 2;


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
        float halfCircleWidth = (float)glutGet(GLUT_WINDOW_WIDTH) / nrColoane / (float)glutGet(GLUT_WINDOW_WIDTH) * 2 / 3;
        float halfCircleHeight = (float)glutGet(GLUT_WINDOW_WIDTH) / nrLinii / (float)glutGet(GLUT_WINDOW_WIDTH) * 2 / 3;
        /*glPolygonMode(GL_FRONT, GL_FILL);
        glBegin(GL_QUADS);glVertex2f(x- halfCircleWidth,y - halfCircleHeight);
        glVertex2f(x + halfCircleWidth, y - halfCircleHeight);
        glVertex2f(x + halfCircleWidth, y + halfCircleHeight);
        glVertex2f(x - halfCircleWidth, y + halfCircleHeight);
        glEnd();*/
        float XpixelInRelativeUnit = (float)1 / (float)glutGet(GLUT_WINDOW_WIDTH) / 2;
        float YpixelInRelativeUnit = (float)1 / (float)glutGet(GLUT_WINDOW_WIDTH) / 2;

        float cx = x + XpixelInRelativeUnit / 2, cy = y + YpixelInRelativeUnit / 2;
        float radius = halfCircleWidth;

        //top
            //decupare in jos
        for (x = cx; x <= cx + halfCircleWidth; x += XpixelInRelativeUnit) {
            //right
            float circleY = cy + sqrt(radius * radius - (x - cx) * (x - cx));
            glBegin(GL_QUADS);
            glVertex2f(x, circleY);
            glVertex2f(x + XpixelInRelativeUnit, circleY);
            glVertex2f(x + XpixelInRelativeUnit, circleY + YpixelInRelativeUnit);
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
        for (y = cy; y <= cy + halfCircleHeight; y += YpixelInRelativeUnit) {
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

        //bottom
        for (x = cx; x <= cx + halfCircleWidth; x += XpixelInRelativeUnit) {
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
        for (y = cy; y >= cy - halfCircleHeight; y -= YpixelInRelativeUnit) {
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

    void deseneazaGrila() {
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
            glVertex2f(-1, (float)linie / (nrLinii - 1) * 2 - 1);
            glVertex2f(1, (float)linie / (nrLinii - 1) * 2 - 1);
            glEnd();
        }
    }

    void deseneazaMartorCerc(int cx, int cy, int R) {
        double XpixelInRelativeUnit = (double)1 / ((double)glutGet(GLUT_WINDOW_WIDTH) / 2);
        double YpixelInRelativeUnit = (double)1 / ((double)glutGet(GLUT_WINDOW_WIDTH) / 2);

        glColor3f(1, 0, 0);

        double realcx = -1, realcy = -1;

        double windowWidth = (float)glutGet(GLUT_WINDOW_WIDTH);
        double columnSizeInPixels = windowWidth / (nrColoane - 1);
        double radiusInRelative = R * columnSizeInPixels * XpixelInRelativeUnit;

        //top
            //decupare in jos
        for (double x = realcx; x <= realcx + radiusInRelative; x += XpixelInRelativeUnit) {
            //right
            float circleY = realcy + sqrt(radiusInRelative * radiusInRelative - (x - realcx) * (x - realcx));
            glBegin(GL_QUADS);
            glVertex2f(x, circleY);
            glVertex2f(x + XpixelInRelativeUnit, circleY);
            glVertex2f(x + XpixelInRelativeUnit, circleY + YpixelInRelativeUnit);
            glVertex2f(x, circleY + YpixelInRelativeUnit);
            glEnd();
        }
        //decupare la stanga
        for (double y = realcy + radiusInRelative; y >= realcy; y -= YpixelInRelativeUnit) {
            //right
            float circleX = realcx + sqrt(radiusInRelative * radiusInRelative - (y - realcy) * (y - realcy));
            glBegin(GL_QUADS);
            glVertex2f(circleX, y);
            glVertex2f(circleX + XpixelInRelativeUnit, y);
            glVertex2f(circleX + XpixelInRelativeUnit, y + YpixelInRelativeUnit);
            glVertex2f(circleX, y + YpixelInRelativeUnit);
            glEnd();
        }
    }
};


void AfisarePuncteCerc4(int x, int y, vector<pair<int, int>> &M) {
    M.push_back({ x,y });
}


void AfisareCerc4(int cx, int cy, int R, vector<pair<int,int>> &M)
{
    //incep cu punctul de pe axa ox deoarece are coordonate intregi spre deosebire de cel de pe bisectoare
    int x = R, y = 0;
    /*variabilele de decizie si regulile de incrementare nu se modifica deoarece
    in punctul de start se inverseaza doar x cu y, iar functia F este comutativa din
    punctul de vedere al parametrilor
    */
    int d = 1 - R;
    int dN = 3, dNV = -2 * R + 5;
    M = {};
    AfisarePuncteCerc4(x, y, M);
    /*in primul octant x adica cosinusul e mai mare decat sinusul adica y*/
    while (y < x)
    {
        if (d < 0)
        {
            //alegem pixelul N
            d += dN;
            dN += 2;
            dNV += 2;
        }
        else
        {
            //alegem pixelul NV
            d += dNV;
            dN += 2;
            dNV += 4;
            //scadem x in loc de y pentru a merge spre pixelul NV
            x--;
        }
        //crestem y in loc de x pentru ca parcurgem cercul de jos in sus
        y++;
        AfisarePuncteCerc4(x, y, M);
    }
}

void DesenareCerc4(int cx,int cy,int R,GrilaCarteziana g) {
    vector<pair<int, int>> M = {};
    AfisareCerc4(cx, cy, R, M);
    for (pair<int, int> punct : M) {
        g.writePixel(punct.first-1, punct.second);
        g.writePixel(punct.first, punct.second);
        g.writePixel(punct.first+1, punct.second);
    }
}

void Display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    GrilaCarteziana g;
    g.nrColoane = 16;
    g.nrLinii = 16;
    g.deseneazaGrila();
    g.deseneazaMartorCerc(0, 0, 13);
    DesenareCerc4(0, 0, 13,g);
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