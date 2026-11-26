#include <GL/freeglut.h> //library untuk buat window
#include <cmath> //untuk fungsi mtk (sin dan cos untuk buat lingkaran/ellipse)

using namespace std;

// ==========================================
// Fungsi membuat ellipse/lingkaran
// cx = posisi pusat ellipse/lingkaran di sumbu x
// cy = posisi pusat ellipse/lingkaran di sumbu y
// rx = jari-jari horizontal ellipse
// ry = jari-jari vertikal ellipse
// ==========================================
void drawEllipse(float cx, float cy, float rx, float ry)
{
    glBegin(GL_TRIANGLE_FAN); //menggambar ellipse dengan metode triangle fan

    glVertex2f(cx, cy); 

    for (int i = 0; i <= 100; i++) 
    {
        float angle = 2.0f * 3.14159f * i / 100.0f; // rumus sudut 360 derajat

        float x = cx + rx * cos(angle); // menghitung koordinat x titik pada ellipse (cos untuk menentukan posisi horizontal)
        float y = cy + ry * sin(angle); // menghitung koordinat y titik pada ellipse (sin untuk menentukan posisi vertical)

        glVertex2f(x, y); //memasukkan titik hasil perhitungan ke OpenGL
    }

    glEnd();
}

// ==========================================
// Fungsi membuat outline ellipse
// ==========================================
void drawEllipseOutline(float cx, float cy, float rx, float ry)
{
    glBegin(GL_LINE_LOOP); //untuk membuat outline garis yang menghubungkan semua titik dan otomatis kembali ke awal

    for (int i = 0; i < 100; i++) //looping untuk membuat 100 titik pada outline ellipse
    {
        float angle = 2.0f * 3.14159f * i / 100.0f; //mengubah indeks titik menjadi sudut 0 sampai hampir 2n

        float x = cx + rx * cos(angle);
        float y = cy + ry * sin(angle);

        glVertex2f(x, y);
    }

    glEnd(); //mengakhiri pembuatan outline ellipse
}

// ==========================================
// Fungsi membuat lingkaran
// ==========================================
void drawCircle(float cx, float cy, float radius)
{
    glBegin(GL_TRIANGLE_FAN); //membuat lingkaran yang terisi

    glVertex2f(cx, cy); //tipus lingkaran

    for (int i = 0; i <= 100; i++)//looping untuk membuat 100 titik pada lingkaran
    {
        float angle = 2.0f * 3.14159f * i / 100.0f;

        float x = cx + radius * cos(angle);
        float y = cy + radius * sin(angle);

        glVertex2f(x, y);
    }

    glEnd(); //mengakhiri pembuatan lingkaran
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

        float x = cx + radius * cos(angle);
        float y = cy + radius * sin(angle);

        glVertex2f(x, y);
    }

    glEnd();
}

// ==========================================
// Fungsi membuat langit luar angkasa dan bintang
// ==========================================
void drawSpace()
{
    // ======================================
    // Bintang kecil
    // ======================================
    glColor3f(0.85f, 0.90f, 1.0f); //warna bintang

    glPointSize(2.0f); //ukuran titik bintang

    glBegin(GL_POINTS); //berarti setiap vartex akan ditampilkan sebagai satu titik

        //setiap glVertex2f() adalah koordinat titik bintang
        glVertex2f(-0.90f,  0.75f);
        glVertex2f(-0.72f,  0.55f);
        glVertex2f(-0.52f,  0.82f);
        glVertex2f(-0.30f,  0.68f);
        glVertex2f(-0.08f,  0.88f);
        glVertex2f( 0.20f,  0.72f);
        glVertex2f( 0.43f,  0.85f);
        glVertex2f( 0.67f,  0.62f);
        glVertex2f( 0.88f,  0.80f);

        glVertex2f(-0.82f,  0.25f);
        glVertex2f(-0.60f,  0.35f);
        glVertex2f(-0.40f,  0.20f);
        glVertex2f(-0.18f,  0.38f);
        glVertex2f( 0.05f,  0.28f);
        glVertex2f( 0.32f,  0.42f);
        glVertex2f( 0.55f,  0.25f);
        glVertex2f( 0.78f,  0.38f);

        glVertex2f(-0.90f, -0.05f);
        glVertex2f(-0.68f, -0.25f);
        glVertex2f(-0.45f, -0.10f);
        glVertex2f(-0.25f, -0.35f);
        glVertex2f( 0.02f, -0.20f);
        glVertex2f( 0.28f, -0.38f);
        glVertex2f( 0.52f, -0.15f);
        glVertex2f( 0.75f, -0.30f);
        glVertex2f( 0.92f, -0.08f);

        glVertex2f(-0.80f, -0.60f);
        glVertex2f(-0.55f, -0.78f);
        glVertex2f(-0.30f, -0.62f);
        glVertex2f(-0.05f, -0.82f);
        glVertex2f( 0.22f, -0.65f);
        glVertex2f( 0.48f, -0.80f);
        glVertex2f( 0.72f, -0.58f);
        glVertex2f( 0.90f, -0.75f);

    glEnd();


    // ======================================
    // Bintang yang sedikit lebih terang
    // ======================================
    glColor3f(1.0f, 1.0f, 0.95f); //warna bintang lebih terang

    glPointSize(3.0f); //ukuran titik bintang lebih besar

    glBegin(GL_POINTS); 

        glVertex2f(-0.55f,  0.60f);
        glVertex2f(-0.15f,  0.55f);
        glVertex2f( 0.38f,  0.65f);
        glVertex2f( 0.82f,  0.48f);

        glVertex2f(-0.75f, -0.42f);
        glVertex2f(-0.35f, -0.50f);
        glVertex2f( 0.45f, -0.48f);
        glVertex2f( 0.82f, -0.52f);

    glEnd();


    // ======================================
    // Bintang besar berbentuk silang
    // ======================================
    glColor3f(0.75f, 0.80f, 1.0f);

    glLineWidth(1.5f); //ketebalan garis

    glBegin(GL_LINES); //membuat garis berdasarkan pasangan vartex

        // Bintang kiri atas
        // dua vartex pertamam membentu vertikal
        glVertex2f(-0.70f, 0.70f);
        glVertex2f(-0.70f, 0.78f);

        // dua vartex kedua membentu horizontal
        glVertex2f(-0.74f, 0.74f);
        glVertex2f(-0.66f, 0.74f);

        // Bintang kanan atas
        glVertex2f(0.70f, 0.72f);
        glVertex2f(0.70f, 0.82f);

        glVertex2f(0.65f, 0.77f);
        glVertex2f(0.75f, 0.77f);

        // Bintang kiri bawah
        glVertex2f(-0.78f, -0.65f);
        glVertex2f(-0.78f, -0.55f);

        glVertex2f(-0.83f, -0.60f);
        glVertex2f(-0.73f, -0.60f);

        // Bintang kanan bawah
        glVertex2f(0.65f, -0.65f);
        glVertex2f(0.65f, -0.55f);

        glVertex2f(0.60f, -0.60f);
        glVertex2f(0.70f, -0.60f);

    glEnd();
}

// ==========================================
// Fungsi membuat api / sinar UFO
// ==========================================
void drawFire()
{
    // Api kuning
    glColor3f(1.0f, 0.85f, 0.0f); //warna api kuning

    glBegin(GL_POLYGON); //untuk membuat bidang tertutup

        //setiap vartex membentuk sudut api
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
    // agar transofrmasi ufo tidak memengaruhi objek lain yang digambar setelhnya
    glPushMatrix();

    glRotatef(-8.0f, 0.0f, 0.0f, 1.0f); //memutar sebesar -8 derajat

    // ======================================
    // 1. Api di bawah UFO
    // ======================================
    drawFire(); // panggil fungsi api sebelumnya

    // ======================================
    // 2. Kubah kaca
    // ======================================
    glColor3f(0.65f, 0.65f, 0.95f);

    //memanggil fungsi drawEllipse untuk membuat kubah kaca
    drawEllipse(
        0.0f,
        0.18f,
        0.48f,
        0.40f
    );

    // Outline kubah
    glColor3f(0.0f, 0.0f, 0.0f); //hitam

    glLineWidth(5.0f); //ketebalan garis outline kubah

    drawEllipseOutline(
        0.0f,
        0.18f,
        0.48f,
        0.40f
    );

    // ======================================
    // 3. Badan UFO
    // ======================================
    glColor3f(0.60f, 0.60f, 0.62f); //abu

    drawEllipse(
        0.0f,
        -0.10f,
        0.75f, //ufo lebih lebar
        0.25f //ufo lebih tinggi 
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

    // Menggambar langit luar angkasa dan bintang
    drawSpace();

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

    // Ukuran window 800x600 piksel
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