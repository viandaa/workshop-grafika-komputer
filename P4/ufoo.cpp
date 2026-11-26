#include <GL/freeglut.h>
#include <cmath>

// ==========================================
// Fungsi membuat ellipse
// ==========================================
void drawEllipse(float cx, float cy, float rx, float ry)
{
    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(cx, cy);

    for (int i = 0; i <= 100; i++)
    {
        float angle = 2.0f * 3.14159f * i / 100.0f;

        float x = cx + rx * std::cos(angle);
        float y = cy + ry * std::sin(angle);

        glVertex2f(x, y);
    }

    glEnd();
}

// ==========================================
// Fungsi membuat outline ellipse
// ==========================================
void drawEllipseOutline(float cx, float cy, float rx, float ry)
{
    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < 100; i++)
    {
        float angle = 2.0f * 3.14159f * i / 100.0f;

        float x = cx + rx * std::cos(angle);
        float y = cy + ry * std::sin(angle);

        glVertex2f(x, y);
    }

    glEnd();
}

// ==========================================
// Fungsi membuat lingkaran
// ==========================================
void drawCircle(float cx, float cy, float radius)
{
    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(cx, cy);

    for (int i = 0; i <= 100; i++)
    {
        float angle = 2.0f * 3.14159f * i / 100.0f;

        float x = cx + radius * std::cos(angle);
        float y = cy + radius * std::sin(angle);

        glVertex2f(x, y);
    }

    glEnd();
}

// ==========================================
// Fungsi membuat outline lingkaran
// ==========================================
void drawCircleOutline(float cx, float cy, float radius)
{
    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < 100; i++)
    {
        float angle = 2.0f * 3.14159f * i / 100.0f;

        float x = cx + radius * std::cos(angle);
        float y = cy + radius * std::sin(angle);

        glVertex2f(x, y);
    }

    glEnd();
}

// ==========================================
// Fungsi membuat api / sinar UFO
// ==========================================
void drawFire()
{
    // Api kuning
    glColor3f(1.0f, 0.85f, 0.0f);

    glBegin(GL_POLYGON);

        glVertex2f(-0.35f, -0.30f);
        glVertex2f(-0.50f, -0.60f);
        glVertex2f(-0.30f, -0.55f);
        glVertex2f(-0.25f, -0.85f);
        glVertex2f( 0.00f, -0.60f);
        glVertex2f( 0.20f, -0.85f);
        glVertex2f( 0.18f, -0.50f);
        glVertex2f( 0.40f, -0.60f);
        glVertex2f( 0.28f, -0.30f);

    glEnd();

    // Api oranye
    glColor3f(1.0f, 0.35f, 0.0f);

    glBegin(GL_POLYGON);

        glVertex2f(-0.25f, -0.30f);
        glVertex2f(-0.30f, -0.55f);
        glVertex2f(-0.10f, -0.45f);
        glVertex2f( 0.00f, -0.65f);
        glVertex2f( 0.10f, -0.45f);
        glVertex2f( 0.25f, -0.55f);
        glVertex2f( 0.18f, -0.30f);

    glEnd();

    // Api merah
    glColor3f(0.9f, 0.15f, 0.05f);

    glBegin(GL_POLYGON);

        glVertex2f(-0.15f, -0.30f);
        glVertex2f(-0.10f, -0.48f);
        glVertex2f( 0.00f, -0.40f);
        glVertex2f( 0.08f, -0.50f);
        glVertex2f( 0.12f, -0.30f);

    glEnd();
}

// ==========================================
// Fungsi membuat UFO
// ==========================================
void drawUFO()
{
    // Membuat semua bagian UFO sedikit miring
    glPushMatrix();

    glRotatef(-8.0f, 0.0f, 0.0f, 1.0f);

    // ======================================
    // 1. Api di bawah UFO
    // ======================================
    drawFire();

    // ======================================
    // 2. Kubah kaca
    // ======================================
    glColor3f(0.65f, 0.65f, 0.95f);

    drawEllipse(
        0.0f,
        0.18f,
        0.48f,
        0.40f
    );

    // Outline kubah
    glColor3f(0.0f, 0.0f, 0.0f);

    glLineWidth(5.0f);

    drawEllipseOutline(
        0.0f,
        0.18f,
        0.48f,
        0.40f
    );

    // ======================================
    // 3. Badan UFO
    // ======================================
    glColor3f(0.60f, 0.60f, 0.62f);

    drawEllipse(
        0.0f,
        -0.10f,
        0.75f,
        0.25f
    );

    // Outline badan
    glColor3f(0.0f, 0.0f, 0.0f);

    glLineWidth(6.0f);

    drawEllipseOutline(
        0.0f,
        -0.10f,
        0.75f,
        0.25f
    );

    // ======================================
    // 4. Garis pembatas badan dan kaca
    // ======================================
    glColor3f(0.0f, 0.0f, 0.0f);

    glLineWidth(5.0f);

    glBegin(GL_LINE_STRIP);

        glVertex2f(-0.65f, -0.05f);
        glVertex2f(-0.35f, -0.13f);
        glVertex2f( 0.00f, -0.18f);
        glVertex2f( 0.35f, -0.13f);
        glVertex2f( 0.65f, -0.05f);

    glEnd();

    // ======================================
    // 5. Lampu UFO
    // ======================================

    // Lampu 1
    glColor3f(0.35f, 1.0f, 0.45f);
    drawCircle(-0.45f, -0.10f, 0.075f);

    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(4.0f);
    drawCircleOutline(-0.45f, -0.10f, 0.075f);

    // Lampu 2
    glColor3f(0.35f, 1.0f, 0.45f);
    drawCircle(-0.15f, -0.17f, 0.075f);

    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircleOutline(-0.15f, -0.17f, 0.075f);

    // Lampu 3
    glColor3f(0.35f, 1.0f, 0.45f);
    drawCircle(0.15f, -0.17f, 0.075f);

    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircleOutline(0.15f, -0.17f, 0.075f);

    // Lampu 4
    glColor3f(0.35f, 1.0f, 0.45f);
    drawCircle(0.45f, -0.10f, 0.075f);

    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircleOutline(0.45f, -0.10f, 0.075f);

    glPopMatrix();
}

// ==========================================
// Fungsi Display
// ==========================================
void display()
{
    // Membersihkan layar
    glClear(GL_COLOR_BUFFER_BIT);

    // 4 bintang
    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(4.0f);

    glBegin(GL_POINTS);
        glVertex2f(0.75f, 0.75f);
        glVertex2f(-0.75f, 0.70f);
        glVertex2f(0.60f, 0.45f);
        glVertex2f(-0.55f, 0.35f);
    glEnd();

    // Menggambar UFO
    drawUFO();

    // Menampilkan hasil
    glFlush();
}

// ==========================================
// Fungsi Inisialisasi
// ==========================================
void init()
{
    // Background
    glClearColor(
        0.05f,
        0.05f,
        0.12f,
        1.0f
    );

    // Projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Koordinat 2D
    gluOrtho2D(
        -1.0,
         1.0,
        -1.0,
         1.0
    );

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// ==========================================
// Fungsi Main
// ==========================================
int main(int argc, char** argv)
{
    // Inisialisasi GLUT
    glutInit(&argc, argv);

    // Mode tampilan
    glutInitDisplayMode(
        GLUT_SINGLE | GLUT_RGB
    );

    // Ukuran window
    glutInitWindowSize(
        800,
        600
    );

    // Posisi window
    glutInitWindowPosition(
        100,
        100
    );

    // Judul window
    glutCreateWindow(
        "UFO - Grafika Komputer"
    );

    // Inisialisasi
    init();

    // Memanggil display
    glutDisplayFunc(display);

    // Menjalankan program
    glutMainLoop();

    return 0;
}