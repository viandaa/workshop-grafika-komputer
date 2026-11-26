#include <GL/freeglut.h>
#include <stdlib.h>

// ==============================
// VARIABEL SKALA OBJEK
// ==============================

float scale = 1.0f;


// ==============================
// FUNGSI UNTUK MENGGAMBAR OBJEK
// ==============================

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();

    // Scaling objek
    glScalef(scale, scale, 1.0f);

    // Menggambar segitiga
    glBegin(GL_TRIANGLES);

        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(0.0f, 0.6f);

        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(-0.5f, -0.4f);

        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(0.5f, -0.4f);

    glEnd();

    glPopMatrix();

    glutSwapBuffers();
}


// ==============================
// FUNGSI KEYBOARD
// ==============================

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        // Memperbesar objek
        case 'w':
        case 'W':
            scale += 0.1f;
            break;

        // Memperkecil objek
        case 's':
        case 'S':
            scale -= 0.1f;

            // Batas agar objek tidak menjadi terlalu kecil
            if (scale < 0.1f)
                scale = 0.1f;

            break;

        // ESC untuk keluar
        case 27:
            exit(0);
            break;
    }

    glutPostRedisplay();
}


// ==============================
// INITIALIZATION
// ==============================

void init()
{
    // Background putih
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


// ==============================
// MAIN PROGRAM
// ==============================

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(800, 600);

    glutInitWindowPosition(100, 100);

    glutCreateWindow("Scaling - OpenGL");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}