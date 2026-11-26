
#include <GL/freeglut.h>

// ==========================================
// Variabel rotasi
// ==========================================
static float rotasiX = 20.0f;
static float rotasiY = 0.0f;

// ==========================================
// Fungsi menggambar manusia salju
// ==========================================
void drawSnowman()
{
    // Badan bawah
    glPushMatrix();
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(0.0f, -0.65f, 0.0f);
        glutWireSphere(0.55f, 20, 20);
    glPopMatrix();

    // Badan tengah
    glPushMatrix();
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(0.0f, 0.10f, 0.0f);
        glutWireSphere(0.40f, 20, 20);
    glPopMatrix();

    // Kepala
    glPushMatrix();
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(0.0f, 0.85f, 0.0f);
        glutWireSphere(0.28f, 20, 20);
    glPopMatrix();

    // Mata kiri
    glPushMatrix();
        glColor3f(0.0f, 0.0f, 0.0f);
        glTranslatef(-0.10f, 0.90f, 0.24f);
        glutWireSphere(0.035f, 10, 10);
    glPopMatrix();

    // Mata kanan
    glPushMatrix();
        glColor3f(0.0f, 0.0f, 0.0f);
        glTranslatef(0.10f, 0.90f, 0.24f);
        glutWireSphere(0.035f, 10, 10);
    glPopMatrix();

    // Hidung wortel
    glPushMatrix();
        glColor3f(1.0f, 0.4f, 0.0f);
        glTranslatef(0.0f, 0.82f, 0.25f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        glutWireCone(0.07f, 0.25f, 10, 10);
    glPopMatrix();

    // Topi
    glPushMatrix();
        glColor3f(0.0f, 0.0f, 1.0f);
        glTranslatef(0.0f, 1.12f, 0.0f);
        glutWireCone(0.25f, 0.35f, 15, 15);
    glPopMatrix();

    // Kancing
    glColor3f(0.0f, 0.0f, 0.0f);

    glPushMatrix();
        glTranslatef(0.0f, 0.25f, 0.38f);
        glutWireSphere(0.04f, 10, 10);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f, 0.05f, 0.40f);
        glutWireSphere(0.04f, 10, 10);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f, -0.15f, 0.40f);
        glutWireSphere(0.04f, 10, 10);
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

    glTranslatef(0.0f, 0.0f, -4.0f);

    glRotatef(rotasiX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotasiY, 0.0f, 1.0f, 0.0f);

    drawSnowman();

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

    glutCreateWindow("Manusia Salju 3D");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
