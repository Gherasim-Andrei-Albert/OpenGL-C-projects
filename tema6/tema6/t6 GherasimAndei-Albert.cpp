
#include <stdlib.h>
#include <glut.h>

#include <stdio.h>
#include <math.h>

// dimensiunea ferestrei in pixeli
#define dim 300

unsigned char prevKey;

enum EObiect { cubw, cubs, sferaw, sferas };
EObiect ob = cubw;

void DisplayAxe() {
    int X, Y, Z;
    X = Y = 200;
    Z = 200;

    glLineWidth(2);

    // axa Ox - verde
    glColor3f(0, 1, 0);
    glBegin(GL_LINE_STRIP);
    glVertex3f(0, 0, 0);
    glVertex3f(X, 0, 0);
    glEnd();

    // axa Oy - albastru
    glColor3f(0, 0, 1);
    glBegin(GL_LINE_STRIP);
    glVertex3f(0, 0, 0);
    glVertex3f(0, Y, 0);
    glEnd();

    // axa Oz - rosu
    glColor3f(1, 0, 0);
    glBegin(GL_LINE_STRIP);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, Z);
    glEnd();

    glLineWidth(1);
}

// cub wireframe
void Display1() {
    glColor3f(1, 0, 0);
    glutWireCube(1);
}

// cub solid
void Display2() {
    glColor3f(1, 0, 0);
    glutSolidCube(1);
}

// sfera wireframe
void Display3() {
    glColor3f(0, 0, 1);
    glutWireSphere(1, 10, 10);
}

// sfera solida
void Display4() {
    glColor3f(0, 0, 1);
    glutSolidSphere(1, 10, 10);
}

void DisplayObiect()
{
    switch (ob)
    {
    case cubw:
        Display1();
        break;
    case cubs:
        Display2();
        break;
    case sferaw:
        Display3();
        break;
    case sferas:
        Display4();
        break;
    default:
        break;
    }
}

// rotatia cu un unghi de 10 grade in raport cu axa x
void DisplayX() {
    glMatrixMode(GL_MODELVIEW);
    glRotated(10, 1, 0, 0);
}

// rotatia cu un unghi de 10 grade in raport cu axa y
void DisplayY() {
    glMatrixMode(GL_MODELVIEW);
    glRotated(10, 0, 1, 0);
}

// rotatia cu un unghi de 10 grade in raport cu axa z
void DisplayZ() {
    glMatrixMode(GL_MODELVIEW);
    glRotated(10, 0, 0, 1);
}

// Translatia cu 0.2, 0.2, 0.2
void DisplayT() {
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(0.2, 0.2, 0.2);
}

// Scalarea cu 1.2, 1.2, 1.2
void DisplayS() {
    glMatrixMode(GL_MODELVIEW);
    glScalef(1.2, 1.2, 1.2);
}

void Init(void) {
    glClearColor(1, 1, 1, 1);
    glLineWidth(2);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10, 10, -10, 10, 30, -30);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotated(20, 1, 0, 0);
    glRotated(-20, 0, 1, 0);
}

void matMul(double T[4][4], double p[4]) {
    for (int i = 0; i < 4; ++i) {
        double suma = 0;
        for (int j = 0; j < 4; ++j) {
            suma += T[i][j] * p[j];
        }
        p[i] = suma;
    }
}

void Display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    DisplayAxe();
    double triangle[3][4] = {
        {2,3,0,1},
        {7,5,7,1},
        {7,10,7,1}
    };

    /*double x1 = triangle[0][0], y1 = triangle[0][1], z1 = triangle[0][2],
        x2 = triangle[1][0], y2 = triangle[1][1], z2 = triangle[1][2],
        x3 = triangle[2][0], y3 = triangle[2][1], z3 = triangle[2][2];
    */

    glBegin(GL_TRIANGLES);
    for (auto p : triangle) {
        glVertex3d(p[0], p[1], p[2]);
    }
    glEnd();
    glutSwapBuffers();

    double T[4][4] = {
        {1, 0, 0, -triangle[0][0]},
        {0, 1, 0, -triangle[0][1]},
        {0, 0, 1, -triangle[0][2]},
        {0, 0, 0, 1}
    };
    switch (prevKey)
    {
    case '1':

        glClear(GL_COLOR_BUFFER_BIT);
        DisplayAxe();


        /*double d1 = sqrt((x2 - x1) * (x2 - x1) + (z2 - z1) * (z2 - z1));
        double d2 = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) + (z2 - z1) * (z2 - z1));

        double M[4][4] = {
            {(z2-z1)/d1, 0, -(x2-x1)/d1, (x2*z1-x1*z2)/d1},
            {-((x2-x1)*(y2-y1))/(d1*d2), d1/d2, -((y2-y1)*(z2-z1))/(d1*d2), (((y1-y2)*(x1*x1+z1*z1-x1*x2-y1*z2))/(d1*d2))-(y1*y2)/d2},
            {(x2-x1)/d2, (y2-y1)/d2, (z2-z1)/d2, (x1*x1+y1*y1+z1*z1-x1*x2-y1*y2-z1*z2)/d2},
            {0, 0, 0, 1}
        };

        for (int i = 0; i < 3; ++i) {
            matMul(M, triangle[i]);
        }

        glBegin(GL_TRIANGLES);
        for (auto p : triangle) {
            glVertex3d(p[0], p[1], p[2]);
        }*/


        //P1
        for (int i = 0; i < 3; ++i) {
            matMul(T, triangle[i]);
        }

        //P2
        double d1 = sqrt(triangle[2][0] * triangle[2][0] + triangle[2][2] * triangle[2][2]);

        double tgTetha = triangle[1][2] / triangle[1][0];
        double tetha = atan(tgTetha) * (180 / (atan(1) * 4));
        double rot[4][4] = {
            {cos((tetha - 90) * ((atan(1) * 4) / 180)), 0, sin((tetha - 90) * ((atan(1) * 4) / 180)), 0},
            {0, 1, 0, 0},
            {-sin((tetha - 90) * ((atan(1) * 4) / 180)), 0, cos((tetha - 90) * ((atan(1) * 4) / 180)), 0},
            {0, 0, 0, 1}
        };
        for (int i = 0; i < 3; ++i) {
            matMul(rot, triangle[i]);
        }

        //P3
        double d2 = sqrt(triangle[1][1] * triangle[1][1] + triangle[1][2] * triangle[1][2]);
        double cosPhi = triangle[1][2] / d2;
        double phi = acos(cosPhi);

        double rot2[4][4] = {
            {1, 0, 0, 0},
            {0, cos(phi), -sin(phi), 0},
            {0, sin(phi), cos(phi), 0},
            {0, 0, 0, 1}
        };

        for (int i = 0; i < 3; ++i) {
            matMul(rot2, triangle[i]);
        }

        glBegin(GL_TRIANGLES);
        for (auto p : triangle) {
            glVertex3d(p[0], p[1], p[2]);
        }
        glEnd();

        for (auto p : triangle) {
            printf("%f %f %f %f\n", p[0], p[1], p[2], p[3]);
        }


        //P4*/
        double d3 = sqrt(triangle[2][0] * triangle[2][0] + triangle[2][1] * triangle[2][1]);
        double cosAlpha = triangle[2][1] / d3;
        double alpha = acos(cosAlpha);
        double rot3[4][4] = {
            {cos(alpha), -sin(alpha), 0, 0},
            {sin(alpha), cos(alpha), 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
        };

        for (int i = 0; i < 3; ++i) {
            matMul(rot3, triangle[i]);
        }

        glBegin(GL_TRIANGLES);
        for (auto p : triangle) {
            glVertex3d(p[0], p[1], p[2]);
        }
        glEnd();

        for (auto p : triangle) {
            printf("%f %f %f %f\n", p[0], p[1], p[2], p[3]);
        }

        glutSwapBuffers();
        break;
    }
}

void Reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void KeyboardFunc(unsigned char key, int x, int y) {
    prevKey = key;
    if (key == 27) // escape
        exit(0);
    glutPostRedisplay();
}

void MouseFunc(int button, int state, int x, int y) {
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);

    glutInitWindowSize(dim, dim);

    glutInitWindowPosition(100, 100);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutCreateWindow(argv[0]);

    Init();

    glutReshapeFunc(Reshape);

    glutKeyboardFunc(KeyboardFunc);

    glutMouseFunc(MouseFunc);

    glutDisplayFunc(Display);

    glutMainLoop();

    return 0;
}