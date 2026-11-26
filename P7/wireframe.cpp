
#include <GL/freeglut.h>

// ==========================================
// Variabel rotasi
// ==========================================
static float rotasiX = 20.0f;
static float rotasiY = 0.0f;

// ==========================================
// Fungsi menggambar objek 3D
// ==========================================
void drawObjects()
{
    // Bola pertama - Biru
    glPushMatrix();
        glColor3f(0.0f, 0.0f, 1.0f);
        glTranslatef(0.45f, 0.35f, 0.0f);
        glutWireSphere(0.75f, 20, 20);
    glPopMatrix();

    // Bola kedua - Magenta
    glPushMatrix();
        glColor3f(1.0f, 0.0f, 1.0f);
        glTranslatef(-0.45f, -0.35f, 0.0f);
        glutWireSphere(0.65f, 20, 20);
    glPopMatrix();

    // Bola ketiga - Hijau
    glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);
        glTranslatef(0.0f, 0.0f, 0.2f);
        glutWireSphere(0.35f, 20, 20);
    glPopMatrix();
}

// ==========================================
// Fungsi Display
// ==========================================
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -3.0f);
    glRotatef(rotasiX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotasiY, 0.0f, 1.0f, 0.0f);

    drawObjects();

    glutSwapBuffers();
}

// ==========================================
// Fungsi Reshape
// ==========================================
void reshape(int w, int h)
{
    if (h == 0) h = 1;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0, (float)w / h, 1.0, 10.0);

    glMatrixMode(GL_MODELVIEW);
}

// ==========================================
// Fungsi Keyboard
// ==========================================
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'w':
            rotasiX -= 5.0f;
            break;
        case 's':
            rotasiX += 5.0f;
            break;
        case 'a':
            rotasiY -= 5.0f;
            break;
        case 'd':
            rotasiY += 5.0f;
            break;
    }

    glutPostRedisplay();
}

// ==========================================
// Fungsi Inisialisasi
// ==========================================
void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

// ==========================================
// Fungsi Main
// ==========================================
int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Tugas Objek 3D");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
