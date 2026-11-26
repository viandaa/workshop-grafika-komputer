
#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>

// ============================================================
// 1. KONSTANTA UKURAN LAYAR
// ============================================================

// WIDTH menentukan lebar window permainan.
// HEIGHT menentukan tinggi window permainan.
//
// Ukuran layar digunakan sebagai batas koordinat objek
// ketika menggambar background, player, dan bintang.

const int WIDTH = 1000;
const int HEIGHT = 650;

const float PI = 3.14159265f;

// Jumlah maksimal bintang yang dapat muncul bersamaan.
const int MAX_OBJECTS = 20;

// Jumlah bintang kecil yang digunakan sebagai dekorasi background.
const int TOTAL_STARS = 100;


// ============================================================
// 2. STRUKTUR DATA BINTANG
// ============================================================

// struct digunakan untuk mengelompokkan beberapa variabel
// yang menjadi informasi dari satu objek bintang.
//
// Setiap bintang mempunyai:
// x      = posisi horizontal
// y      = posisi vertikal
// speed  = kecepatan gerak bintang
// active = status apakah bintang sedang aktif atau tidak

struct Object {
    float x, y;
    float speed;
    bool active;
};

// Array untuk menyimpan seluruh bintang yang muncul
// selama permainan berlangsung.
Object objects[MAX_OBJECTS];


// ============================================================
// 3. DATA BINTANG DEKORASI BACKGROUND
// ============================================================

// Array ini menyimpan koordinat bintang-bintang kecil
// yang digunakan sebagai hiasan luar angkasa.
//
// Bintang dekorasi berbeda dengan bintang yang dikumpulkan.
// Bintang dekorasi tidak bergerak dan tidak menambah skor.

float bgStarX[TOTAL_STARS];
float bgStarY[TOTAL_STARS];


// ============================================================
// 4. VARIABEL PLAYER / ASTRONAUT
// ============================================================

// playerX = posisi horizontal astronaut.
// playerY = posisi vertikal astronaut.
//
// Posisi awal astronaut berada di sebelah kiri layar
// dan berdiri di atas lantai permainan.

float playerX = 130;
float playerY = 100;

// jumpVelocity menyimpan kecepatan vertikal astronaut
// ketika sedang melakukan gerakan melompat.

float jumpVelocity = 0;

// JUMP_POWER menentukan kekuatan awal lompatan.
// GRAVITY memberikan efek gravitasi agar astronaut
// kembali turun setelah mencapai titik tertinggi.

const float JUMP_POWER = 13.0f;
const float GRAVITY = 0.55f;

// jumping digunakan untuk mengetahui apakah astronaut
// sedang berada dalam kondisi melompat.

bool jumping = false;

// crouching digunakan untuk mengetahui apakah astronaut
// sedang berada dalam posisi menunduk.
//
// false = berdiri
// true  = menunduk

bool crouching = false;


// ============================================================
// 5. VARIABEL PERMAINAN
// ============================================================

// score menyimpan jumlah skor pemain.
// lives menyimpan jumlah nyawa.
// timeLeft menyimpan sisa waktu permainan.

int score = 0;
int lives = 3;
int timeLeft = 60;

// spawnTimer digunakan untuk mengatur kemunculan bintang.
// gameTimer digunakan untuk menghitung waktu permainan.

int spawnTimer = 0;
int gameTimer = 0;

// gameOver menentukan apakah permainan sudah selesai.
//
// false = permainan masih berjalan
// true  = permainan sudah berakhir

bool gameOver = false;


// ============================================================
// 6. FUNGSI drawRect()
// ============================================================

// Fungsi ini digunakan untuk menggambar persegi
// dan persegi panjang menggunakan OpenGL.
//
// Parameter:
// x, y = posisi awal objek
// w    = lebar objek
// h    = tinggi objek
// r, g, b = komposisi warna RGB
//
// Fungsi ini digunakan untuk membuat:
// - Badan astronaut
// - Kepala astronaut
// - Kaki dan sepatu astronaut
// - Panel dada
// - Tangki oksigen
// - Lantai permainan
// - Garis dekorasi lantai
//
// GL_QUADS digunakan untuk menggambar bidang
// yang mempunyai empat titik sudut.

void drawRect(float x, float y, float w, float h,
              float r, float g, float b) {

    // Mengatur warna objek berdasarkan nilai RGB.
    glColor3f(r, g, b);

    // Memulai proses menggambar persegi panjang.
    glBegin(GL_QUADS);

    // Titik pertama: sudut kiri bawah.
    glVertex2f(x, y);

    // Titik kedua: sudut kanan bawah.
    glVertex2f(x + w, y);

    // Titik ketiga: sudut kanan atas.
    glVertex2f(x + w, y + h);

    // Titik keempat: sudut kiri atas.
    glVertex2f(x, y + h);

    // Mengakhiri proses menggambar.
    glEnd();
}


// ============================================================
// 7. FUNGSI drawCircle()
// ============================================================

// Fungsi ini digunakan untuk menggambar lingkaran.
//
// Parameter:
// x, y = titik pusat lingkaran
// radius = ukuran jari-jari lingkaran
// r, g, b = warna lingkaran
//
// Fungsi ini digunakan untuk membuat:
// - Planet
// - Kawah pada permukaan planet
// - Indikator nyawa
//
// GL_TRIANGLE_FAN digunakan untuk membentuk lingkaran
// dari kumpulan segitiga yang bertemu pada titik pusat.

void drawCircle(float x, float y, float radius,
                float r, float g, float b) {

    // Mengatur warna lingkaran.
    glColor3f(r, g, b);

    // Memulai proses menggambar lingkaran.
    glBegin(GL_TRIANGLE_FAN);

    // Menentukan titik pusat lingkaran.
    glVertex2f(x, y);

    // Membuat 60 segmen agar bentuk lingkaran terlihat halus.
    for (int i = 0; i <= 60; i++) {

        // Menghitung sudut setiap titik dalam radian.
        float angle = 2 * PI * i / 60;

        // Menghitung koordinat titik pada keliling lingkaran
        // menggunakan fungsi cos dan sin.
        glVertex2f(
            x + cos(angle) * radius,
            y + sin(angle) * radius
        );
    }

    // Mengakhiri proses menggambar lingkaran.
    glEnd();
}


// ============================================================
// 8. FUNGSI drawText()
// ============================================================

// Fungsi ini digunakan untuk menampilkan tulisan
// pada window permainan.
//
// Parameter:
// x   = posisi horizontal tulisan
// y   = posisi vertikal tulisan
// str = teks yang akan ditampilkan
//
// Fungsi ini digunakan untuk menampilkan:
// - SCORE
// - LIVES
// - TIME
// - Petunjuk kontrol
// - Tulisan GAME OVER

void drawText(float x, float y, std::string str) {

    // Mengatur warna tulisan menjadi putih.
    glColor3f(1.0f, 1.0f, 1.0f);

    // Menentukan posisi awal tulisan.
    glRasterPos2f(x, y);

    // Menampilkan setiap karakter menggunakan font GLUT.
    for (char c : str) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}


// ============================================================
// 9. FUNGSI drawStar()
// ============================================================

// Fungsi ini digunakan untuk menggambar bintang
// yang menjadi objek utama untuk dikumpulkan pemain.
//
// Parameter:
// x    = posisi horizontal pusat bintang
// y    = posisi vertikal pusat bintang
// size = ukuran bintang
//
// Bintang mempunyai lima ujung.
// Bentuknya dibuat menggunakan 10 titik yang bergantian
// antara radius luar dan radius bagian dalam.
//
// Warna kuning digunakan agar bintang mudah dibedakan
// dari planet yang hanya berfungsi sebagai dekorasi.

void drawStar(float x, float y, float size) {

    // Mengatur warna bintang menjadi kuning.
    glColor3f(1.0f, 0.85f, 0.0f);

    // Memulai proses menggambar bentuk bintang.
    glBegin(GL_TRIANGLE_FAN);

    // Menentukan titik pusat bintang.
    glVertex2f(x, y);

    // Menghasilkan 10 titik untuk membentuk lima ujung bintang.
    for (int i = 0; i <= 10; i++) {

        // Menghitung sudut setiap titik.
        float angle = PI / 2 + i * PI / 5;

        // Radius bergantian antara ujung luar
        // dan bagian dalam bintang.
        float radius = (i % 2 == 0)
                       ? size
                       : size * 0.45f;

        // Menghitung posisi setiap titik bintang.
        glVertex2f(
            x + cos(angle) * radius,
            y + sin(angle) * radius
        );
    }

    // Mengakhiri proses menggambar bintang.
    glEnd();
}


// ============================================================
// 10. FUNGSI drawBackground()
// ============================================================

// Fungsi ini digunakan untuk menggambar seluruh
// bagian latar belakang permainan.
//
// Isi background:
// 1. Latar luar angkasa.
// 2. Bintang-bintang kecil dekorasi.
// 3. Planet beserta detail permukaannya.
// 4. Cincin planet.
// 5. Lantai permainan.
//
// Planet hanya berfungsi sebagai hiasan.
// Planet tidak dimasukkan ke dalam array objects
// sehingga tidak dapat dikumpulkan oleh player.

void drawBackground() {

    // Menggambar background berwarna hitam kebiruan.
    drawRect(
        0, 0, WIDTH, HEIGHT,
        0.0f, 0.0f, 0.015f
    );

    // Menggambar bintang kecil dekorasi.
    // Posisi bintang diambil dari array bgStarX dan bgStarY.
    for (int i = 0; i < TOTAL_STARS; i++) {

        drawRect(
            bgStarX[i],
            bgStarY[i],
            3, 3,
            1.0f, 1.0f, 1.0f
        );
    }

    // --------------------------------------------------------
    // PLANET DEKORASI
    // --------------------------------------------------------

    // Lingkaran utama planet menggunakan warna oranye kecokelatan.
    // Warna ini berbeda dengan astronaut dan bintang kuning.
    drawCircle(
        150, 490, 80,
        0.65f, 0.25f, 0.10f
    );

    // Lingkaran-lingkaran kecil menjadi detail permukaan planet.
    // Setiap lingkaran memiliki warna dan ukuran berbeda.

    drawCircle(
        125, 510, 17,
        0.80f, 0.38f, 0.18f
    );

    drawCircle(
        175, 465, 13,
        0.45f, 0.16f, 0.08f
    );

    drawCircle(
        180, 525, 9,
        0.85f, 0.45f, 0.20f
    );

    drawCircle(
        115, 455, 8,
        0.45f, 0.16f, 0.08f
    );

    // Menggambar cincin planet menggunakan GL_LINE_LOOP.
    // GL_LINE_LOOP menghubungkan titik-titik menjadi garis tertutup.
    glColor3f(0.95f, 0.65f, 0.35f);

    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < 100; i++) {

        float angle = 2 * PI * i / 100;

        // Menghitung koordinat titik pembentuk cincin.
        glVertex2f(
            150 + cos(angle) * 110,
            490 + sin(angle) * 30
        );
    }

    glEnd();

    // --------------------------------------------------------
    // LANTAI PERMAINAN
    // --------------------------------------------------------

    // Bagian utama lantai berwarna biru.
    drawRect(
        0, 65, WIDTH, 35,
        0.0f, 0.25f, 0.85f
    );

    // Bagian bawah lantai berwarna biru lebih gelap.
    drawRect(
        0, 45, WIDTH, 20,
        0.0f, 0.08f, 0.35f
    );

    // Membuat garis-garis dekorasi pada lantai.
    // Perulangan membuat garis dengan jarak 100 piksel.
    for (int i = 0; i < WIDTH; i += 100) {

        drawRect(
            i, 75, 50, 3,
            0.2f, 0.6f, 1.0f
        );
    }
}


// ============================================================
// 11. FUNGSI drawPlayer()
// ============================================================

// Fungsi ini digunakan untuk menggambar karakter utama,
// yaitu astronaut.
//
// Astronaut dibuat dari beberapa persegi panjang
// yang disusun menjadi satu karakter.
//
// Bagian karakter:
// - Kaki dan sepatu
// - Badan
// - Panel dada
// - Tangan
// - Kepala atau helm
// - Kaca helm
// - Tangki oksigen
//
// Variabel crouching menentukan bentuk astronaut.
//
// Jika crouching = false:
// Astronaut digambar dalam posisi berdiri.
//
// Jika crouching = true:
// Astronaut digambar dalam posisi menunduk.
//
// Variabel playerY digunakan agar seluruh karakter
// dapat bergerak naik dan turun ketika melompat.

void drawPlayer() {

    // Mengambil koordinat posisi astronaut.
    float x = playerX;
    float y = playerY;

    // --------------------------------------------------------
    // KONDISI ASTRONAUT BERDIRI
    // --------------------------------------------------------

    if (!crouching) {

        // Menggambar kaki kiri dan kanan.
        drawRect(
            x + 10, y, 18, 30,
            0.9f, 0.9f, 0.9f
        );

        drawRect(
            x + 40, y, 18, 30,
            0.9f, 0.9f, 0.9f
        );

        // Menggambar sepatu berwarna biru.
        drawRect(
            x + 5, y, 25, 8,
            0.0f, 0.3f, 0.9f
        );

        drawRect(
            x + 38, y, 25, 8,
            0.0f, 0.3f, 0.9f
        );

        // Menggambar badan utama astronaut.
        drawRect(
            x + 5, y + 30, 60, 55,
            0.95f, 0.95f, 0.95f
        );

        // Menggambar panel dada astronaut.
        drawRect(
            x + 22, y + 48, 25, 18,
            0.0f, 0.3f, 0.9f
        );

        // Menggambar tangan kiri dan kanan.
        drawRect(
            x - 10, y + 40, 15, 35,
            0.8f, 0.8f, 0.8f
        );

        drawRect(
            x + 65, y + 40, 15, 35,
            0.8f, 0.8f, 0.8f
        );

        // Menggambar kepala atau helm astronaut.
        drawRect(
            x + 5, y + 85, 60, 55,
            0.95f, 0.95f, 0.95f
        );

        // Menggambar kaca helm berwarna biru gelap.
        drawRect(
            x + 13, y + 95, 44, 35,
            0.0f, 0.05f, 0.25f
        );

        // Menggambar pantulan cahaya pada kaca helm.
        drawRect(
            x + 20, y + 115, 7, 10,
            0.3f, 0.7f, 1.0f
        );

        // Menggambar tangki oksigen di belakang astronaut.
        drawRect(
            x - 15, y + 35, 12, 65,
            0.0f, 0.3f, 0.95f
        );
    }

    // --------------------------------------------------------
    // KONDISI ASTRONAUT MENUNDUK
    // --------------------------------------------------------

    else {

        // Kaki astronaut dalam posisi menunduk.
        drawRect(
            x + 5, y, 30, 15,
            0.9f, 0.9f, 0.9f
        );

        drawRect(
            x + 35, y, 30, 15,
            0.9f, 0.9f, 0.9f
        );

        // Sepatu astronaut.
        drawRect(
            x, y, 30, 8,
            0.0f, 0.3f, 0.9f
        );

        drawRect(
            x + 35, y, 30, 8,
            0.0f, 0.3f, 0.9f
        );

        // Badan astronaut dalam bentuk lebih pendek.
        drawRect(
            x + 5, y + 15, 65, 30,
            0.95f, 0.95f, 0.95f
        );

        // Panel dada.
        drawRect(
            x + 30, y + 23, 20, 13,
            0.0f, 0.3f, 0.9f
        );

        // Kepala atau helm dalam posisi menunduk.
        drawRect(
            x + 45, y + 35, 38, 35,
            0.95f, 0.95f, 0.95f
        );

        // Kaca helm.
        drawRect(
            x + 52, y + 43, 27, 20,
            0.0f, 0.05f, 0.25f
        );

        // Tangki oksigen.
        drawRect(
            x - 5, y + 15, 12, 35,
            0.0f, 0.3f, 0.95f
        );
    }
}


// ============================================================
// 12. FUNGSI drawObjects()
// ============================================================

// Fungsi ini digunakan untuk menggambar seluruh
// bintang yang sedang aktif dalam permainan.
//
// Program memeriksa setiap slot pada array objects.
// Jika status active bernilai true, bintang akan digambar.
//
// Posisi gambar mengikuti koordinat x dan y
// yang tersimpan dalam masing-masing objek.

void drawObjects() {

    for (int i = 0; i < MAX_OBJECTS; i++) {

        // Jika bintang tidak aktif, proses dilewati.
        if (!objects[i].active)
            continue;

        // Menggambar bintang dengan ukuran 22.
        drawStar(
            objects[i].x,
            objects[i].y,
            22
        );
    }
}


// ============================================================
// 13. FUNGSI spawnObject()
// ============================================================

// Fungsi ini digunakan untuk memunculkan bintang baru.
//
// Bintang muncul dari sebelah kanan layar.
// Posisi vertikalnya dibuat secara acak tetapi dibatasi
// agar bintang masih dapat dijangkau oleh astronaut.
//
// Nilai posisi Y berada pada rentang 110 sampai 289.
//
// Kecepatan bintang dibuat acak antara 3 sampai 5.

void spawnObject() {

    // Mencari slot kosong pada array bintang.
    for (int i = 0; i < MAX_OBJECTS; i++) {

        // Slot yang tidak aktif dapat digunakan kembali.
        if (!objects[i].active) {

            // Menentukan posisi awal bintang di kanan layar.
            objects[i].x = WIDTH + 30;

            // Mengacak ketinggian bintang.
            // Rentang ini dibuat agar bintang tidak terlalu tinggi.
            objects[i].y = 110 + rand() % 180;

            // Menentukan kecepatan bintang secara acak.
            objects[i].speed = 3 + rand() % 3;

            // Mengaktifkan bintang.
            objects[i].active = true;

            // Menghentikan pencarian setelah satu slot ditemukan.
            break;
        }
    }
}


// ============================================================
// 14. FUNGSI collision()
// ============================================================

// Fungsi ini digunakan untuk mendeteksi tabrakan
// antara dua objek dalam permainan.
//
// Parameter:
// x1, y1 = posisi objek pertama
// x2, y2 = posisi objek kedua
// distance = batas jarak tabrakan
//
// Pada game ini, fungsi collision digunakan untuk
// mendeteksi apakah astronaut berhasil menyentuh bintang.
//
// Perhitungan menggunakan rumus Pythagoras:
// jarak = akar dari (selisih X kuadrat + selisih Y kuadrat)
//
// Jika jarak lebih kecil dari batas distance,
// kedua objek dianggap bertabrakan.

bool collision(float x1, float y1,
               float x2, float y2,
               float distance) {

    // Menghitung selisih posisi horizontal.
    float dx = x1 - x2;

    // Menghitung selisih posisi vertikal.
    float dy = y1 - y2;

    // Menghitung jarak antara kedua titik.
    float d = sqrt(dx * dx + dy * dy);

    // Mengembalikan true jika jarak berada dalam batas collision.
    return d < distance;
}


// ============================================================
// 15. FUNGSI drawHUD()
// ============================================================

// HUD (Heads-Up Display) merupakan bagian layar
// yang menampilkan informasi permainan.
//
// Informasi yang ditampilkan:
// - SCORE: jumlah skor pemain.
// - LIVES: jumlah nyawa.
// - TIME: sisa waktu permainan.
// - Petunjuk tombol untuk mengendalikan astronaut.
//
// HUD membantu pemain mengetahui kondisi permainan
// tanpa harus menghentikan permainan.

void drawHUD() {

    // Membuat teks skor menggunakan stringstream.
    std::stringstream ss;
    ss << "SCORE : " << score;

    // Menampilkan skor di bagian kiri atas layar.
    drawText(30, 615, ss.str());

    // Membuat teks waktu.
    std::stringstream tt;
    tt << "TIME : " << timeLeft;

    // Menampilkan waktu di bagian kanan atas layar.
    drawText(850, 615, tt.str());

    // Menampilkan label jumlah nyawa.
    drawText(450, 615, "LIVES :");

    // Menggambar indikator nyawa berbentuk lingkaran merah.
    for (int i = 0; i < lives; i++) {

        drawCircle(
            525 + i * 30,
            610,
            10,
            1.0f, 0.0f, 0.0f
        );
    }

    // Menampilkan petunjuk kontrol di bawah layar.
    drawText(
        30, 20,
        "SPACE : JUMP     S / DOWN : CROUCH"
    );
}


// ============================================================
// 16. FUNGSI drawGameOver()
// ============================================================

// Fungsi ini digunakan untuk menampilkan tampilan
// ketika waktu permainan sudah habis.
//
// Informasi yang ditampilkan:
// - Tulisan GAME OVER.
// - Skor akhir pemain.
// - Instruksi tombol R untuk mengulang permainan.

void drawGameOver() {

    // Menggambar kotak latar belakang Game Over.
    drawRect(
        300, 220, 400, 200,
        0.0f, 0.05f, 0.2f
    );

    // Menampilkan tulisan GAME OVER.
    drawText(425, 360, "GAME OVER");

    // Menampilkan skor akhir pemain.
    std::stringstream ss;
    ss << "FINAL SCORE : " << score;

    drawText(420, 310, ss.str());

    // Menampilkan petunjuk untuk mengulang permainan.
    drawText(
        385, 265,
        "PRESS R TO RESTART"
    );
}


// ============================================================
// 17. FUNGSI display()
// ============================================================

// Fungsi display bertugas menampilkan seluruh
// objek dan informasi permainan ke layar.
//
// Urutan penggambaran:
// 1. Membersihkan layar.
// 2. Menggambar background.
// 3. Menggambar bintang yang aktif.
// 4. Menggambar astronaut.
// 5. Menggambar HUD.
// 6. Menggambar Game Over jika permainan selesai.
//
// Fungsi ini dipanggil oleh GLUT setiap kali
// layar perlu digambar ulang.

void display() {

    // Membersihkan buffer warna sebelum menggambar frame baru.
    glClear(GL_COLOR_BUFFER_BIT);

    // Menggambar latar belakang dan dekorasi.
    drawBackground();

    // Menggambar seluruh bintang yang aktif.
    drawObjects();

    // Menggambar karakter astronaut.
    drawPlayer();

    // Menggambar informasi skor, nyawa, dan waktu.
    drawHUD();

    // Jika permainan selesai, tampilkan Game Over.
    if (gameOver) {
        drawGameOver();
    }

    // Menampilkan hasil gambar ke layar.
    // Double buffering membantu mengurangi kedipan gambar.
    glutSwapBuffers();
}


// ============================================================
// 18. FUNGSI resetGame()
// ============================================================

// Fungsi ini digunakan untuk mengembalikan
// permainan ke kondisi awal.
//
// Fungsi dipanggil ketika pemain menekan tombol R
// setelah tampilan Game Over muncul.

void resetGame() {

    // Mengembalikan skor ke nol.
    score = 0;

    // Mengembalikan nyawa ke tiga.
    lives = 3;

    // Mengembalikan waktu ke 60 detik.
    timeLeft = 60;

    // Mengembalikan posisi astronaut ke posisi awal.
    playerY = 100;

    // Mengatur ulang kecepatan lompatan.
    jumpVelocity = 0;

    // Mengembalikan status lompatan dan menunduk.
    jumping = false;
    crouching = false;

    // Mengatur ulang penghitung waktu dan kemunculan bintang.
    spawnTimer = 0;
    gameTimer = 0;

    // Mengubah status permainan menjadi aktif kembali.
    gameOver = false;

    // Menonaktifkan semua bintang yang masih tersimpan.
    for (int i = 0; i < MAX_OBJECTS; i++) {
        objects[i].active = false;
    }
}


// ============================================================
// 19. FUNGSI update()
// ============================================================

// Fungsi update merupakan pusat pengaturan logika permainan.
//
// Bagian yang diperbarui:
// 1. Gerakan lompatan astronaut.
// 2. Pengaruh gravitasi.
// 3. Kemunculan bintang.
// 4. Pergerakan bintang.
// 5. Deteksi tabrakan bintang dengan astronaut.
// 6. Penambahan skor.
// 7. Pengurangan waktu permainan.
// 8. Kondisi Game Over.
//
// Fungsi ini dipanggil berulang kali menggunakan
// glutTimerFunc() agar gerakan permainan berjalan terus.

void update(int value) {

    // Logika permainan hanya dijalankan jika belum Game Over.
    if (!gameOver) {

        // ----------------------------------------------------
        // A. GERAKAN LOMPAT ASTRONAUT
        // ----------------------------------------------------

        // Jika jumping bernilai true, astronaut sedang melompat.
        if (jumping) {

            // Menambahkan kecepatan vertikal ke posisi Y.
            // Nilai positif membuat astronaut bergerak ke atas.
            playerY += jumpVelocity;

            // Gravitasi mengurangi kecepatan lompatan.
            // Akibatnya astronaut akan melambat saat naik
            // lalu bergerak turun kembali.
            jumpVelocity -= GRAVITY;

            // Memeriksa apakah astronaut sudah menyentuh lantai.
            if (playerY <= 100) {

                // Mengembalikan posisi ke atas lantai.
                playerY = 100;

                // Menghentikan kecepatan lompatan.
                jumpVelocity = 0;

                // Mengubah status menjadi tidak melompat.
                jumping = false;
            }
        }

        // ----------------------------------------------------
        // B. MENGATUR KEMUNCULAN BINTANG
        // ----------------------------------------------------

        // Penghitung bertambah setiap kali update dijalankan.
        spawnTimer++;

        // Setiap 35 kali update, bintang baru dimunculkan.
        if (spawnTimer >= 35) {

            spawnObject();

            // Mengatur ulang penghitung kemunculan bintang.
            spawnTimer = 0;
        }

        // ----------------------------------------------------
        // C. MENGGERAKKAN DAN MEMERIKSA COLLISION BINTANG
        // ----------------------------------------------------

        for (int i = 0; i < MAX_OBJECTS; i++) {

            // Melewati slot jika bintang tidak aktif.
            if (!objects[i].active)
                continue;

            // Mengurangi koordinat X agar bintang bergerak
            // dari kanan menuju kiri layar.
            objects[i].x -= objects[i].speed;

            // Menentukan titik tengah astronaut untuk collision.
            float playerCenterX;
            float playerCenterY;

            // Titik collision disesuaikan dengan bentuk astronaut.
            if (crouching && !jumping) {

                // Titik tengah ketika astronaut menunduk.
                playerCenterX = playerX + 42;
                playerCenterY = playerY + 35;
            }
            else {

                // Titik tengah ketika astronaut berdiri atau melompat.
                playerCenterX = playerX + 35;
                playerCenterY = playerY + 65;
            }

            // Memeriksa apakah astronaut menyentuh bintang.
            if (collision(
                playerCenterX,
                playerCenterY,
                objects[i].x,
                objects[i].y,
                40
            )) {

                // Menambah skor sebanyak 10 poin.
                score += 10;

                // Menonaktifkan bintang setelah berhasil dikumpulkan.
                objects[i].active = false;

                // Melanjutkan ke bintang berikutnya.
                continue;
            }

            // Menonaktifkan bintang jika sudah melewati layar kiri.
            if (objects[i].x < -30) {
                objects[i].active = false;
            }
        }

        // ----------------------------------------------------
        // D. MENGATUR TIMER PERMAINAN
        // ----------------------------------------------------

        // Menghitung jumlah pemanggilan update.
        gameTimer++;

        // Update dijadwalkan setiap 16 milidetik.
        // 63 kali update kira-kira sama dengan satu detik.
        if (gameTimer >= 63) {

            // Mengurangi waktu permainan satu detik.
            timeLeft--;

            // Mengatur ulang penghitung waktu.
            gameTimer = 0;
        }

        // ----------------------------------------------------
        // E. KONDISI GAME OVER
        // ----------------------------------------------------

        // Permainan selesai ketika waktu mencapai nol.
        if (timeLeft <= 0) {
            gameOver = true;
        }
    }

    // Meminta GLUT menggambar ulang layar.
    glutPostRedisplay();

    // Menjadwalkan pemanggilan update berikutnya
    // setelah 16 milidetik.
    glutTimerFunc(16, update, 0);
}


// ============================================================
// 20. FUNGSI keyboardDown()
// ============================================================

// Fungsi ini menangani input dari keyboard biasa.
//
// Tombol SPACE:
// Membuat astronaut melompat.
//
// Tombol S atau s:
// Membuat astronaut menunduk.
//
// Tombol R atau r:
// Mengulang permainan ketika Game Over.
//
// Tombol ESC:
// Keluar dari permainan.

void keyboardDown(unsigned char key, int x, int y) {

    // SPACE digunakan untuk melompat.
    // Lompatan hanya bisa dilakukan jika permainan aktif
    // dan astronaut belum sedang melompat.
    if (key == ' ' && !gameOver && !jumping) {

        jumping = true;

        // Memberikan kecepatan awal ke arah atas.
        jumpVelocity = JUMP_POWER;

        // Membatalkan posisi menunduk ketika melompat.
        crouching = false;
    }

    // Tombol S atau s digunakan untuk menunduk.
    // Player tidak dapat menunduk saat sedang melompat.
    if ((key == 's' || key == 'S') &&
        !gameOver && !jumping) {

        crouching = true;
    }

    // Tombol R atau r digunakan untuk mengulang permainan.
    if ((key == 'r' || key == 'R') && gameOver) {
        resetGame();
    }

    // Tombol ESC memiliki kode ASCII 27.
    // Digunakan untuk keluar dari program.
    if (key == 27) {
        exit(0);
    }
}


// ============================================================
// 21. FUNGSI keyboardUp()
// ============================================================

// Fungsi ini mendeteksi ketika tombol keyboard dilepaskan.
//
// Ketika tombol S dilepaskan, astronaut kembali berdiri.
// Nilai crouching diubah menjadi false.

void keyboardUp(unsigned char key, int x, int y) {

    if (key == 's' || key == 'S') {
        crouching = false;
    }
}


// ============================================================
// 22. FUNGSI specialDown()
// ============================================================

// Fungsi ini menangani tombol khusus pada keyboard.
//
// Tombol khusus berbeda dengan tombol biasa.
// Contohnya adalah tombol panah atas, bawah, kiri, dan kanan.
//
// Pada game ini, tombol panah bawah digunakan
// untuk membuat astronaut menunduk.

void specialDown(int key, int x, int y) {

    // GLUT_KEY_DOWN merupakan kode tombol panah bawah.
    if (key == GLUT_KEY_DOWN && !gameOver && !jumping) {
        crouching = true;
    }
}


// ============================================================
// 23. FUNGSI specialUp()
// ============================================================

// Fungsi ini mendeteksi ketika tombol khusus dilepaskan.
//
// Ketika panah bawah dilepaskan, astronaut kembali berdiri.

void specialUp(int key, int x, int y) {

    if (key == GLUT_KEY_DOWN) {
        crouching = false;
    }
}


// ============================================================
// 24. FUNGSI init()
// ============================================================

// Fungsi init digunakan untuk melakukan pengaturan awal OpenGL.
//
// Pengaturan yang dilakukan:
// 1. Menentukan warna dasar layar.
// 2. Mengatur sistem proyeksi.
// 3. Mengatur koordinat 2D.
// 4. Mengacak posisi bintang dekorasi.
// 5. Menonaktifkan seluruh bintang permainan saat awal.
//
// gluOrtho2D digunakan untuk membuat sistem koordinat 2D.
// Koordinat X dimulai dari 0 sampai WIDTH.
// Koordinat Y dimulai dari 0 sampai HEIGHT.
//
// Titik (0,0) berada di sudut kiri bawah layar.

void init() {

    // Menentukan warna dasar layar menjadi hitam.
    glClearColor(0, 0, 0, 1);

    // Memilih matriks proyeksi.
    glMatrixMode(GL_PROJECTION);

    // Mengembalikan matriks ke kondisi identitas.
    glLoadIdentity();

    // Mengatur sistem koordinat dua dimensi.
    gluOrtho2D(
        0, WIDTH,
        0, HEIGHT
    );

    // Memilih matriks model view.
    glMatrixMode(GL_MODELVIEW);

    // Mengembalikan matriks model view ke kondisi awal.
    glLoadIdentity();

    // Mengacak posisi bintang dekorasi pada background.
    for (int i = 0; i < TOTAL_STARS; i++) {

        bgStarX[i] = rand() % WIDTH;
        bgStarY[i] = rand() % HEIGHT;
    }

    // Menonaktifkan seluruh bintang pada awal permainan.
    for (int i = 0; i < MAX_OBJECTS; i++) {
        objects[i].active = false;
    }
}


// ============================================================
// 25. FUNGSI main()
// ============================================================

// Fungsi main merupakan titik awal program dijalankan.
//
// Tahapan yang dilakukan:
// 1. Mengatur pengacakan posisi objek.
// 2. Menginisialisasi GLUT.
// 3. Menentukan mode tampilan.
// 4. Mengatur ukuran dan posisi window.
// 5. Membuat window permainan.
// 6. Memanggil fungsi init().
// 7. Mendaftarkan fungsi display().
// 8. Mendaftarkan fungsi input keyboard.
// 9. Menjalankan timer update.
// 10. Menjalankan loop utama GLUT.

int main(int argc, char** argv) {

    // Mengatur seed random berdasarkan waktu sistem.
    // Tujuannya agar hasil pengacakan tidak selalu sama
    // setiap kali program dijalankan.
    srand(time(NULL));

    // Menginisialisasi GLUT.
    glutInit(&argc, argv);

    // Mengatur mode tampilan:
    // GLUT_DOUBLE = menggunakan double buffering.
    // GLUT_RGB = menggunakan sistem warna RGB.
    glutInitDisplayMode(
        GLUT_DOUBLE | GLUT_RGB
    );

    // Mengatur ukuran window permainan.
    glutInitWindowSize(
        WIDTH, HEIGHT
    );

    // Mengatur posisi awal window pada layar komputer.
    glutInitWindowPosition(
        100, 50
    );

    // Membuat window dengan judul permainan.
    glutCreateWindow(
        "SPACE CATCHER - OPENGL"
    );

    // Menjalankan pengaturan awal OpenGL.
    init();

    // Mendaftarkan fungsi display sebagai fungsi penggambar.
    glutDisplayFunc(display);

    // Mendaftarkan fungsi input keyboard biasa.
    glutKeyboardFunc(keyboardDown);

    // Mendaftarkan fungsi ketika tombol keyboard dilepaskan.
    glutKeyboardUpFunc(keyboardUp);

    // Mendaftarkan fungsi input tombol khusus.
    glutSpecialFunc(specialDown);

    // Mendaftarkan fungsi ketika tombol khusus dilepaskan.
    glutSpecialUpFunc(specialUp);

    // Menjalankan update pertama setelah 16 milidetik.
    glutTimerFunc(16, update, 0);

    // Menjalankan loop utama GLUT.
    // Program akan terus berjalan sampai window ditutup.
    glutMainLoop();

    return 0;
}
