#include <stdlib.h>
#include <glut.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <float.h>
#include <vector>
#include <string>
#include <iostream>
using namespace std;
#pragma warning(disable:4996)

// dimensiunea ferestrei in pixeli
#define dim 300

unsigned char prevKey;
int nivel = 0;
const double PI = asin(1) * 2;


// dimensiunea ferestrei in pixeli
#define dim 300
// numarul maxim de iteratii pentru testarea apartenentei la mult.Mandelbrot
#define NRITER 5000
// modulul maxim pentru testarea apartenentei la mult.Mandelbrot
#define MODMAX 2
// ratii ptr. Mandelbrot
#define RX 0.01
#define RY 0.01


class CComplex {
public:
    CComplex() : re(0.0), im(0.0) {}
    CComplex(double re1, double im1) : re(re1 * 1.0), im(im1 * 1.0) {}
    CComplex(const CComplex& c) : re(c.re), im(c.im) {}
    ~CComplex() {}

    CComplex operator=(CComplex c)
    {
        re = c.re;
        im = c.im;
        return *this;
    }

    double getRe() { return re; }
    void setRe(double re1) { re = re1; }

    double getIm() { return im; }
    void setIm(double im1) { im = im1; }

    double getModul() { return sqrt(re * re + im * im); }

    int operator==(CComplex& c1)
    {
        return ((re == c1.re) && (im == c1.im));
    }

    CComplex pow2()
    {
        CComplex rez;
        rez.re = powl(re * 1.0, 2) - powl(im * 1.0, 2);
        rez.im = 2.0 * re * im;
        return rez;
    }

    friend CComplex operator+(CComplex& c1, CComplex& c2);
    friend CComplex operator*(CComplex& c1, CComplex& c2);

    void print(FILE* f)
    {
        fprintf(f, "%.20f%+.20f i", re, im);
    }

private:
    double re, im;
};

CComplex operator+(CComplex& c1, CComplex& c2)
{
    CComplex rez(c1.re + c2.re, c1.im + c2.im);
    return rez;
}


CComplex operator*(CComplex& c1, CComplex& c2)
{
    CComplex rez(c1.re * c2.re - c1.im * c2.im,
        c1.re * c2.im + c1.im * c2.re);
    return rez;
}

class CMandelbrot {
public:
    CMandelbrot()
    {
        // m.c se initializeaza implicit cu 0+0i

        m.nriter = NRITER;
        m.modmax = MODMAX;
    }

    ~CMandelbrot() {}

    void setmodmax(double v) { assert(v <= MODMAX); m.modmax = v; }
    double getmodmax() { return m.modmax; }

    void setnriter(int v) { assert(v <= NRITER); m.nriter = v; }
    int getnriter() { return m.nriter; }

    // testeaza daca x apartine multimii Mandelbrot MODMAX
    // returneaza 0 daca apartine, +1 daca converge infinit
    int isIn(CComplex& x)
    {
        int rez = 0;
        CComplex z0, z1;

        z0 = CComplex(0, 0);
        for (int i = 1; i < m.nriter; i++)
        {
            z1 = z0 * z0;
            z1 = z1 + x;
            if (z1.getModul() > m.modmax)
            {
                // x nu apartine m.Mandelbrot deoarece procesul iterativ converge la infinit
                rez = 1;
                break;
            }
            z0 = z1;
        }

        return rez;
    }

    // afisarea multimii Mandelbrot care intersecteaza multimea argument
    void display(double xmin, double ymin, double xmax, double ymax)
    {
        glPushMatrix();
        glLoadIdentity();

        //    glTranslated((xmin + xmax) * 1.0 / (xmin - xmax), (ymin + ymax)  * 1.0 / (ymin - ymax), 0);
        //    glScaled(1.0 / (xmax - xmin), 1.0 / (ymax - ymin), 1);
            // afisarea propriu-zisa
        glBegin(GL_POINTS);
        for (double x = xmin; x <= xmax; x += RX)
            for (double y = ymin; y <= ymax; y += RY)
            {
                CComplex z(x, y);
                int r = isIn(z);
                //        z.print(stdout);
                if (r == 0)
                {
                    //          fprintf(stdout, "   \n");
                    glVertex3d(x, y, 0);
                }
                if (r == 1)
                {
                    //          fprintf(stdout, "   converge infinit\n");
                }
            }
        fprintf(stdout, "STOP\n");
        glEnd();

        glPopMatrix();
    }

private:
    struct SDate {
        // nr. de iteratii
        int nriter;
        // modulul maxim
        double modmax;
    } m;
};

void Display1() {
    CMandelbrot cm;

    glColor3f(1.0, 0.1, 0.1);
    cm.setnriter(30);
    cm.display(-1, -1, 1, 1);
}




class C2coord
{
public:
    C2coord()
    {
        m.x = m.y = 0;
    }

    C2coord(double x, double y)
    {
        m.x = x;
        m.y = y;
    }

    C2coord(C2coord& p)
    {
        m.x = p.m.x;
        m.y = p.m.y;
    }

    C2coord operator=(C2coord p)
    {
        m.x = p.m.x;
        m.y = p.m.y;
        return *this;
    }

    int operator==(C2coord& p)
    {
        return ((m.x == p.m.x) && (m.y == p.m.y));
    }

protected:
    struct SDate
    {
        double x, y;
    } m;
};

class CPunct : public C2coord
{
public:
    CPunct() : C2coord(0.0, 0.0)
    {}

    CPunct(double x, double y) : C2coord(x, y)
    {}

    CPunct(const CPunct &p) : C2coord(p.m.x, p.m.y)
    {}

    CPunct operator=(CPunct p)
    {
        m.x = p.m.x;
        m.y = p.m.y;
        return *this;
    }

    void getxy(double& x, double& y)
    {
        x = m.x;
        y = m.y;
    }

    int operator==(CPunct& p)
    {
        return ((m.x == p.m.x) && (m.y == p.m.y));
    }

    void marcheaza()
    {
        glBegin(GL_POINTS);
        glVertex2d(m.x, m.y);
        glEnd();
    }

    void print(FILE* fis)
    {
        fprintf(fis, "(%+f,%+f)", m.x, m.y);
    }

};

class CVector : public C2coord
{
public:
    CVector() : C2coord(0.0, 0.0)
    {
        normalizare();
    }

    CVector(double x, double y) : C2coord(x, y)
    {
        normalizare();
    }

    CVector operator=(CVector p)
    {
        m.x = p.m.x;
        m.y = p.m.y;
        return *this;
    }

    int operator==(CVector& p)
    {
        return ((m.x == p.m.x) && (m.y == p.m.y));
    }

    CPunct getDest(CPunct& orig, double lungime)
    {
        double x, y;
        orig.getxy(x, y);
        CPunct p(x + m.x * lungime, y + m.y * lungime);
        return p;
    }

    void rotatie(double grade)
    {
        double x = m.x;
        double y = m.y;
        double t = 2 * (4.0 * atan(1)) * grade / 360.0;
        m.x = x * cos(t) - y * sin(t);
        m.y = x * sin(t) + y * cos(t);
        normalizare();
    }

    void deseneaza(CPunct p, double lungime)
    {
        double x, y;
        p.getxy(x, y);
        glColor3f(1.0, 0.1, 0.1);
        glBegin(GL_LINE_STRIP);
        glVertex2d(x, y);
        glVertex2d(x + m.x * lungime, y + m.y * lungime);
        glEnd();
    }

    void print(FILE* fis)
    {
        fprintf(fis, "%+fi %+fj", C2coord::m.x, C2coord::m.y);
    }

private:
    void normalizare()
    {
        double d = sqrt(C2coord::m.x * C2coord::m.x + C2coord::m.y * C2coord::m.y);
        if (d != 0.0)
        {
            C2coord::m.x = C2coord::m.x * 1.0 / d;
            C2coord::m.y = C2coord::m.y * 1.0 / d;
        }
    }
};



void drawIslands(double x, double y, int nivel, double size) {
    glColor3f(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex2d(x - size / 2, y - size / 2);
    glVertex2d(x + size / 2, y - size / 2);
    glVertex2d(x + size / 2, y + size / 2);
    glVertex2d(x - size / 2, y + size / 2);
    glEnd();

    if (nivel != 0) {
        struct point { double x; double y; };
        vector<point> leftSide = { {x - size, y},{x - size ,y + size},{x - size ,y - size} };
        vector<point> rightSide = { {x + size , y},{x + size ,y + size},{x + size ,y - size} };
        vector<point> topSide = { {x,y + size} };
        vector<point> bottomSide = { {x,y - size} };
        vector<vector<point>> sides = { leftSide, rightSide, topSide, bottomSide };
        for (vector<point> side : sides) {
            for (point p : side) {
                drawIslands(p.x, p.y, nivel - 1, size / 3);
            }
        }

    }
}

class Imaginea2
{
public:
    void imaginea2(double lungime,
        int nivel,
        double factordiviziune,
        CPunct p,
        CVector v)
    {
        assert(factordiviziune != 0);
        CPunct p1, p2;
        if (nivel == 0)
        {
        }
        else
        {

            v.rotatie(-45);
            v.deseneaza(p, lungime);
            p1 = v.getDest(p, lungime);
            imaginea2(lungime * factordiviziune, nivel - 1, factordiviziune, p1, v);

            v.rotatie(45+45);
            v.deseneaza(p, lungime);
            p1 = v.getDest(p, lungime);
            p2 = p1;

            v.rotatie(20);
            v.deseneaza(p1, lungime);
            p1 = v.getDest(p1, lungime);
            imaginea2(lungime * factordiviziune, nivel - 1, factordiviziune, p1, v);

            p1 = p2;
            v.rotatie(-20-45);
            v.deseneaza(p1, lungime);
            p1 = v.getDest(p1, lungime);
            p2 = p1;

            v.rotatie(30);
            v.deseneaza(p1, lungime/2);
            p1 = v.getDest(p1, lungime/2);
            imaginea2(lungime * factordiviziune, nivel - 1, factordiviziune, p1, v);

            p1 = p2;
            v.rotatie(-30-90);
            v.deseneaza(p1, lungime/2);
            p1 = v.getDest(p1, lungime/2);
            imaginea2(lungime * factordiviziune, nivel - 1, factordiviziune, p1, v);
        }
    }

    void afisare(double lungime, int nivel)
    {
        CVector v(0.0, 1.0);
        CPunct p(0.0, -1.0);

        v.deseneaza(p, 0.25);
        p = v.getDest(p, 0.25);
        imaginea2(lungime, nivel, (double)1/3, p, v);
    }
};


class Imaginea3
{
public:
    void imaginea3(double lungime, int nivel, CPunct& p, CVector& v, int d)
    {
        if (nivel == 0)
        {
            v.rotatie(-60*d);
            v.deseneaza(p, lungime);
            p = v.getDest(p, lungime);

            v.rotatie(60*d);
            v.deseneaza(p, lungime);
            p = v.getDest(p, lungime);

            v.rotatie(60*d);
            v.deseneaza(p, lungime);
            p = v.getDest(p, lungime);
        }
        else
        {   
            double lungimeaUrmatoare = lungime / ((double)1 + 2*cos((double)60*PI/180));

            v.rotatie(-60*d);
            imaginea3(lungimeaUrmatoare, nivel - 1, p, v, -d);
            v.rotatie(-60*-d);

            v.rotatie(60*d);
            imaginea3(lungimeaUrmatoare, nivel - 1, p, v, d);
            v.rotatie(-60*d);

            v.rotatie(60 * d);
            imaginea3(lungimeaUrmatoare, nivel - 1, p, v, -d);
            v.rotatie(-60 * -d);
        }
    }   

    void afisare(double lungime, int nivel)
    {
        CVector v(0.0, 1.0);
        CPunct p(0.0, 0.0);

        imaginea3(lungime, nivel, p, v, 1);
    }
};



void Display2() {
    drawIslands(0, 0, nivel, (double)2 / 3);
    nivel++;
}

void Display3() {
    Imaginea2 cap;

    
    glPushMatrix();
    glLoadIdentity();
    glScaled(-0.4, -0.4, 1);
    glTranslated(0, -0.5, 0.0);
    cap.afisare(1, nivel);
    glPopMatrix();
    nivel++;
}

void Display4() {
    Imaginea3 cch;
    glPushMatrix();
    glLoadIdentity();
    glTranslated(0, -0.5, 0.0);
    cch.afisare((double)1/2, nivel);
    glPopMatrix();

    nivel++;
}


void Init(void) {

    glClearColor(1.0, 1.0, 1.0, 1.0);

    glLineWidth(1);

    glPointSize(3);

    glPolygonMode(GL_FRONT, GL_LINE);
}

void Display(void)
{
    switch (prevKey)
    {
    case '0':
        glClear(GL_COLOR_BUFFER_BIT);
        nivel = 0;
        fprintf(stderr, "nivel = %d\n", nivel);
        break;
    case '1':
        glClear(GL_COLOR_BUFFER_BIT);
        Display1();
        break;
    case '2':
        glClear(GL_COLOR_BUFFER_BIT);
        Display2();
        break;
    case '3':
        glClear(GL_COLOR_BUFFER_BIT);
        Display3();
        break;
    case '4':
        glClear(GL_COLOR_BUFFER_BIT);
        Display4();
        break;
    default:
        break;
    }

    glFlush();
}

void Reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void KeyboardFunc(unsigned char key, int x, int y)
{
    prevKey = key;
    if (key == 27) // escape
        exit(0);
    glutPostRedisplay();
}

void MouseFunc(int button, int state, int x, int y)
{
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitWindowSize(dim, dim);

    glutInitWindowPosition(100, 100);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutCreateWindow(argv[0]);

    Init();
    
    glutReshapeFunc(Reshape);

    glutKeyboardFunc(KeyboardFunc);

    glutMouseFunc(MouseFunc);

    glutDisplayFunc(Display);

    glutMainLoop();

    return 0;
}


