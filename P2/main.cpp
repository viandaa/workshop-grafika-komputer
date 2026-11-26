#include <GL/glut.h>

// =========================
// PERSEGI MERAH
// =========================
void drawRedSquare()
{
    glBegin(GL_QUADS);

    glColor3f(1.0, 0.0, 0.0);

    glVertex2f(-0.75, 0.45);
    glVertex2f(-0.35, 0.45);
    glVertex2f(-0.35, 0.85);
    glVertex2f(-0.75, 0.85);

    glEnd();
}

// =========================
// HEXAGON KUNING
// =========================
void drawYellowHexagon()
{
    glBegin(GL_POLYGON);

    glColor3f(1.0, 1.0, 0.0);

    glVertex2f(0.55, 0.70);
    glVertex2f(0.70, 0.70);
    glVertex2f(0.80, 0.52);
    glVertex2f(0.70, 0.34);
    glVertex2f(0.55, 0.34);
    glVertex2f(0.45, 0.52);

    glEnd();
}

// =========================
// PERSEGI HIJAU
// =========================
void drawGreenSquare()
{
    glBegin(GL_QUADS);

    glColor3f(0.0, 1.0, 0.0);

    glVertex2f(-0.65, 0.10);
    glVertex2f(-0.25, 0.10);
    glVertex2f(-0.25, -0.30);
    glVertex2f(-0.65, -0.30);

    glEnd();
}

// =========================
// PERSEGI GRADIENT
// =========================
void drawGradientSquare()
{
    glBegin(GL_QUADS);

    // Kiri bawah - hitam
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(-0.85, -0.20);

    // Kanan bawah - abu-abu terang
    glColor3f(0.75, 0.75, 0.75);
    glVertex2f(-0.45, -0.20);

    // Kanan atas - abu-abu terang
    glColor3f(0.75, 0.75, 0.75);
    glVertex2f(-0.45, 0.20);

    // Kiri atas - abu-abu
    glColor3f(0.45, 0.45, 0.45);
    glVertex2f(-0.85, 0.20);

    glEnd();
}

// =========================
// SEGITIGA BIRU
// =========================
void drawBlueTriangle()
{
    glBegin(GL_TRIANGLES);

    glColor3f(0.0, 0.0, 1.0);

    glVertex2f(0.30, -0.30);
    glVertex2f(0.55, 0.35);
    glVertex2f(0.85, -0.30);

    glEnd();
}

// =========================
// SEGITIGA RGB GRADIENT
// =========================
void drawRGBTriangle()
{
    glBegin(GL_TRIANGLES);

    // Merah
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(0.45, -0.05);

    // Hijau
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(0.95, -0.05);

    // Biru
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(0.70, -0.60);

    glEnd();
}

// =========================
// DISPLAY
// =========================
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawRedSquare();
    drawYellowHexagon();
    drawGreenSquare();
    drawGradientSquare();
    drawBlueTriangle();
    drawRGBTriangle();

    glFlush();
}

// =========================
// INIT
// =========================
void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// =========================
// MAIN
// =========================
int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(800, 600);

    glutCreateWindow("Tugas Gambar Primitif");

    init();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}