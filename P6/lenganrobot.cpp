#include <GL/freeglut.h>

// ==========================================
// Variabel sudut rotasi
// ==========================================
static int pundak = 45;
static int siku = 45;

// ==========================================
// Fungsi membuat balok 3D
// ==========================================
void drawBox(float panjang, float tinggi, float depth)
{
    float d = depth;

    // Sisi depan
    glColor3f(0.92f, 0.92f, 0.92f);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, -tinggi / 2);
        glVertex2f(panjang, -tinggi / 2);
        glVertex2f(panjang, tinggi / 2);
        glVertex2f(0.0f, tinggi / 2);
    glEnd();

    // Sisi atas
    glColor3f(0.65f, 0.65f, 0.65f);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, tinggi / 2);
        glVertex2f(panjang, tinggi / 2);
        glVertex2f(panjang - d, tinggi / 2 + d);
        glVertex2f(-d, tinggi / 2 + d);
    glEnd();

    // Sisi samping
    glColor3f(0.55f, 0.55f, 0.55f);
    glBegin(GL_QUADS);
        glVertex2f(panjang, -tinggi / 2);
        glVertex2f(panjang - d, -tinggi / 2 + d);
        glVertex2f(panjang - d, tinggi / 2 + d);
        glVertex2f(panjang, tinggi / 2);
    glEnd();

    // Outline
    glColor3f(0.15f, 0.15f, 0.15f);
    glLineWidth(1.5f);

    glBegin(GL_LINE_LOOP);
        glVertex2f(0.0f, -tinggi / 2);
        glVertex2f(panjang, -tinggi / 2);
        glVertex2f(panjang, tinggi / 2);
        glVertex2f(0.0f, tinggi / 2);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex2f(0.0f, tinggi / 2);
        glVertex2f(panjang, tinggi / 2);
        glVertex2f(panjang - d, tinggi / 2 + d);
        glVertex2f(-d, tinggi / 2 + d);
    glEnd();
}

// ==========================================
// Fungsi menggambar lengan robot
// ==========================================
void drawRobot()
{
    glPushMatrix();

    // 1. Alas robot
    glTranslatef(-0.75f, -0.55f, 0.0f);
    drawBox(0.55f, 0.28f, 0.07f);

    // 2. Persendian pundak
    glTranslatef(0.50f, 0.0f, 0.0f);
    glRotatef((GLfloat)pundak, 0.0f, 0.0f, 1.0f);

    // Lengan atas
    drawBox(0.75f, 0.25f, 0.07f);

    // 3. Persendian siku
    glTranslatef(0.75f, 0.0f, 0.0f);
    glRotatef((GLfloat)siku, 0.0f, 0.0f, 1.0f);

    // Lengan bawah
    drawBox(0.38f, 0.16f, 0.06f);

    // 4. Telapak tangan
    glTranslatef(0.38f, 0.0f, 0.0f);
    drawBox(0.22f, 0.20f, 0.06f);

    // 5. Jari atas
    glPushMatrix();
        glTranslatef(0.18f, 0.07f, 0.0f);
        glRotatef(35.0f, 0.0f, 0.0f, 1.0f);
        drawBox(0.22f, 0.07f, 0.04f);
    glPopMatrix();

    // 6. Jari bawah
    glPushMatrix();
        glTranslatef(0.18f, -0.07f, 0.0f);
        glRotatef(-35.0f, 0.0f, 0.0f, 1.0f);
        drawBox(0.22f, 0.07f, 0.04f);
    glPopMatrix();

    glPopMatrix();
}

// ==========================================
// Fungsi Display
// ==========================================
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    drawRobot();

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

    gluOrtho2D(-1.5, 1.5, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
}

// ==========================================
// Fungsi Keyboard
// ==========================================
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 's':
            pundak = (pundak + 5) % 360;
            break;

        case 'd':
            pundak = (pundak - 5) % 360;
            break;

        case 'w':
            siku = (siku + 5) % 360;
            break;

        case 'e':
            siku = (siku - 5) % 360;
            break;

        default:
            break;
    }

    glutPostRedisplay();
}

// ==========================================
// Fungsi Inisialisasi
// ==========================================
void init(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glShadeModel(GL_FLAT);
}

// ==========================================
// Fungsi Main
// ==========================================
int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Tugas Lengan Robot");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}