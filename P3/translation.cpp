#include <GL/freeglut.h>
#include <stdlib.h>

// ==============================
// VARIABEL POSISI OBJEK
// ==============================

float posX = 0.0f;
float posY = 0.0f;


// ==============================
// FUNGSI UNTUK MENGGAMBAR OBJEK
// ==============================

void display()
{
    // Membersihkan layar
    glClear(GL_COLOR_BUFFER_BIT);

    // Menyimpan kondisi transformasi
    glPushMatrix();

    // ==========================
    // TRANSLATION
    // ==========================

    glTranslatef(posX, posY, 0.0f);

    // ==========================
    // MENGGAMBAR SEGITIGA
    // ==========================

    glBegin(GL_TRIANGLES);

        // Titik atas
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(0.0f, 0.5f);

        // Titik kiri bawah
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(-0.5f, -0.5f);

        // Titik kanan bawah
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(0.5f, -0.5f);

    glEnd();

    // Mengembalikan kondisi transformasi
    glPopMatrix();

    // Menampilkan hasil ke layar
    glutSwapBuffers();
}


// ==============================
// FUNGSI KEYBOARD
// ==============================

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        // ----------------------
        // GERAK KE ATAS
        // ----------------------

        case 'w':
        case 'W':
            posY += 0.1f;
            break;


        // ----------------------
        // GERAK KE BAWAH
        // ----------------------

        case 's':
        case 'S':
            posY -= 0.1f;
            break;


        // ----------------------
        // GERAK KE KIRI
        // ----------------------

        case 'a':
        case 'A':
            posX -= 0.1f;
            break;


        // ----------------------
        // GERAK KE KANAN
        // ----------------------

        case 'd':
        case 'D':
            posX += 0.1f;
            break;


        // ----------------------
        // ESC = KELUAR
        // ----------------------

        case 27:
            exit(0);
            break;
    }

    // Meminta OpenGL menggambar ulang
    glutPostRedisplay();
}


// ==============================
// FUNGSI INISIALISASI
// ==============================

void init()
{
    // Warna background putih
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // Mengatur projection
    glMatrixMode(GL_PROJECTION);

    // Reset matrix
    glLoadIdentity();

    // Mengatur koordinat 2D
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    // Kembali ke model view
    glMatrixMode(GL_MODELVIEW);

    // Reset matrix
    glLoadIdentity();
}


// ==============================
// MAIN PROGRAM
// ==============================

int main(int argc, char** argv)
{
    // Inisialisasi GLUT
    glutInit(&argc, argv);

    // Menggunakan double buffering dan RGB
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // Ukuran window
    glutInitWindowSize(800, 600);

    // Posisi window
    glutInitWindowPosition(100, 100);

    // Membuat window
    glutCreateWindow("Translation - OpenGL");

    // Menjalankan fungsi init
    init();

    // Menentukan fungsi display
    glutDisplayFunc(display);

    // Menentukan fungsi keyboard
    glutKeyboardFunc(keyboard);

    // Menjalankan program
    glutMainLoop();

    return 0;
}
