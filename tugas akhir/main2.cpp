
#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>

// ============================================================
// 1. KONSTANTA UKURAN LAYAR
// ============================================================

const int WIDTH = 1000;
const int HEIGHT = 650;

const float PI = 3.14159265f;

const int MAX_OBJECTS = 20;
const int TOTAL_STARS = 100;

// ============================================================
// 2. STRUKTUR DATA BINTANG
// ============================================================

struct Object {
    float x, y;
    float speed;
    bool active;
};

Object objects[MAX_OBJECTS];

// ============================================================
// 3. DATA BINTANG DEKORASI BACKGROUND
// ============================================================

float bgStarX[TOTAL_STARS];
float bgStarY[TOTAL_STARS];

// ============================================================
// 4. VARIABEL PLAYER / ASTRONAUT
// ============================================================

float playerX = 130;
float playerY = 100;

float jumpVelocity = 0;

const float JUMP_POWER = 13.0f;
const float GRAVITY = 0.55f;

bool jumping = false;
bool crouching = false;

// ============================================================
// 5. VARIABEL ANIMASI GARIS LANTAI
// ============================================================

// Menyimpan posisi pergeseran garis biru muda.
float roadOffset = 0.0f;

// Mengatur kecepatan gerakan garis.
const float roadSpeed = 3.0f;

// ============================================================
// 6. VARIABEL PERMAINAN
// ============================================================

int score = 0;
int lives = 3;
int timeLeft = 60;

int spawnTimer = 0;
int gameTimer = 0;

bool gameOver = false;

// ============================================================
// 7. FUNGSI drawRect()
// ============================================================

void drawRect(float x, float y, float w, float h,
              float r, float g, float b) {

    glColor3f(r, g, b);

    glBegin(GL_QUADS);

    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);

    glEnd();
}

// ============================================================
// 8. FUNGSI drawCircle()
// ============================================================

void drawCircle(float x, float y, float radius,
                float r, float g, float b) {

    glColor3f(r, g, b);

    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(x, y);

    for (int i = 0; i <= 60; i++) {

        float angle = 2 * PI * i / 60;

        glVertex2f(
            x + cos(angle) * radius,
            y + sin(angle) * radius
        );
    }

    glEnd();
}

// ============================================================
// 9. FUNGSI drawText()
// ============================================================

void drawText(float x, float y, std::string str) {

    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(x, y);

    for (char c : str) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

// ============================================================
// 10. FUNGSI drawStar()
// ============================================================

void drawStar(float x, float y, float size) {

    glColor3f(1.0f, 0.85f, 0.0f);

    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(x, y);

    for (int i = 0; i <= 10; i++) {

        float angle = PI / 2 + i * PI / 5;

        float radius = (i % 2 == 0)
                       ? size
                       : size * 0.45f;

        glVertex2f(
            x + cos(angle) * radius,
            y + sin(angle) * radius
        );
    }

    glEnd();
}

// ============================================================
// 11. FUNGSI drawBackground()
// ============================================================

void drawBackground() {

    // Background luar angkasa.
    drawRect(
        0, 0, WIDTH, HEIGHT,
        0.0f, 0.0f, 0.015f
    );

    // Bintang dekorasi background.
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

    drawCircle(
        150, 490, 80,
        0.65f, 0.25f, 0.10f
    );

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

    // Cincin planet.
    glColor3f(0.95f, 0.65f, 0.35f);

    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < 100; i++) {

        float angle = 2 * PI * i / 100;

        glVertex2f(
            150 + cos(angle) * 110,
            490 + sin(angle) * 30
        );
    }

    glEnd();

    // --------------------------------------------------------
    // LANTAI PERMAINAN
    // --------------------------------------------------------

    // Bagian utama lantai.
    drawRect(
        0, 65, WIDTH, 35,
        0.0f, 0.25f, 0.85f
    );

    // Bagian bawah lantai.
    drawRect(
        0, 45, WIDTH, 20,
        0.0f, 0.08f, 0.35f
    );

    // Garis biru muda yang bergerak ke kiri.
    // roadOffset menggeser posisi garis.
    for (int i = -100; i < WIDTH + 100; i += 100) {

        float lineX = i - roadOffset;

        drawRect(
            lineX, 75, 50, 3,
            0.2f, 0.6f, 1.0f
        );
    }
}

// ============================================================
// 12. FUNGSI drawPlayer()
// ============================================================

void drawPlayer() {

    float x = playerX;
    float y = playerY;

    // --------------------------------------------------------
    // ASTRONAUT BERDIRI
    // --------------------------------------------------------

    if (!crouching) {

        // Kaki.
        drawRect(
            x + 10, y, 18, 30,
            0.9f, 0.9f, 0.9f
        );

        drawRect(
            x + 40, y, 18, 30,
            0.9f, 0.9f, 0.9f
        );

        // Sepatu.
        drawRect(
            x + 5, y, 25, 8,
            0.0f, 0.3f, 0.9f
        );

        drawRect(
            x + 38, y, 25, 8,
            0.0f, 0.3f, 0.9f
        );

        // Badan.
        drawRect(
            x + 5, y + 30, 60, 55,
            0.95f, 0.95f, 0.95f
        );

        // Panel dada.
        drawRect(
            x + 22, y + 48, 25, 18,
            0.0f, 0.3f, 0.9f
        );

        // Tangan.
        drawRect(
            x - 10, y + 40, 15, 35,
            0.8f, 0.8f, 0.8f
        );

        drawRect(
            x + 65, y + 40, 15, 35,
            0.8f, 0.8f, 0.8f
        );

        // Kepala / helm.
        drawRect(
            x + 5, y + 85, 60, 55,
            0.95f, 0.95f, 0.95f
        );

        // Kaca helm.
        drawRect(
            x + 13, y + 95, 44, 35,
            0.0f, 0.05f, 0.25f
        );

        // Pantulan kaca.
        drawRect(
            x + 20, y + 115, 7, 10,
            0.3f, 0.7f, 1.0f
        );

        // Tangki oksigen.
        drawRect(
            x - 15, y + 35, 12, 65,
            0.0f, 0.3f, 0.95f
        );
    }

    // --------------------------------------------------------
    // ASTRONAUT MENUNDUK
    // --------------------------------------------------------

    else {

        // Kaki.
        drawRect(
            x + 5, y, 30, 15,
            0.9f, 0.9f, 0.9f
        );

        drawRect(
            x + 35, y, 30, 15,
            0.9f, 0.9f, 0.9f
        );

        // Sepatu.
        drawRect(
            x, y, 30, 8,
            0.0f, 0.3f, 0.9f
        );

        drawRect(
            x + 35, y, 30, 8,
            0.0f, 0.3f, 0.9f
        );

        // Badan.
        drawRect(
            x + 5, y + 15, 65, 30,
            0.95f, 0.95f, 0.95f
        );

        // Panel dada.
        drawRect(
            x + 30, y + 23, 20, 13,
            0.0f, 0.3f, 0.9f
        );

        // Kepala / helm.
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
// 13. FUNGSI drawObjects()
// ============================================================

void drawObjects() {

    for (int i = 0; i < MAX_OBJECTS; i++) {

        if (!objects[i].active)
            continue;

        drawStar(
            objects[i].x,
            objects[i].y,
            22
        );
    }
}

// ============================================================
// 14. FUNGSI spawnObject()
// ============================================================

void spawnObject() {

    for (int i = 0; i < MAX_OBJECTS; i++) {

        if (!objects[i].active) {

            objects[i].x = WIDTH + 30;

            objects[i].y = 110 + rand() % 180;

            objects[i].speed = 3 + rand() % 3;

            objects[i].active = true;

            break;
        }
    }
}

// ============================================================
// 15. FUNGSI collision()
// ============================================================

bool collision(float x1, float y1,
               float x2, float y2,
               float distance) {

    float dx = x1 - x2;
    float dy = y1 - y2;

    float d = sqrt(dx * dx + dy * dy);

    return d < distance;
}

// ============================================================
// 16. FUNGSI drawHUD()
// ============================================================

void drawHUD() {

    std::stringstream ss;
    ss << "SCORE : " << score;

    drawText(30, 615, ss.str());

    std::stringstream tt;
    tt << "TIME : " << timeLeft;

    drawText(850, 615, tt.str());

    drawText(450, 615, "LIVES :");

    for (int i = 0; i < lives; i++) {

        drawCircle(
            525 + i * 30,
            610,
            10,
            1.0f, 0.0f, 0.0f
        );
    }

    drawText(
        30, 20,
        "SPACE : JUMP     S / DOWN : CROUCH"
    );
}

// ============================================================
// 17. FUNGSI drawGameOver()
// ============================================================

void drawGameOver() {

    drawRect(
        300, 220, 400, 200,
        0.0f, 0.05f, 0.2f
    );

    drawText(425, 360, "GAME OVER");

    std::stringstream ss;
    ss << "FINAL SCORE : " << score;

    drawText(420, 310, ss.str());

    drawText(
        385, 265,
        "PRESS R TO RESTART"
    );
}

// ============================================================
// 18. FUNGSI display()
// ============================================================

void display() {

    glClear(GL_COLOR_BUFFER_BIT);

    drawBackground();

    drawObjects();

    drawPlayer();

    drawHUD();

    if (gameOver) {
        drawGameOver();
    }

    glutSwapBuffers();
}

// ============================================================
// 19. FUNGSI resetGame()
// ============================================================

void resetGame() {

    score = 0;
    lives = 3;
    timeLeft = 60;

    playerY = 100;

    jumpVelocity = 0;

    jumping = false;
    crouching = false;

    spawnTimer = 0;
    gameTimer = 0;

    // Mengembalikan posisi garis lantai.
    roadOffset = 0.0f;

    gameOver = false;

    for (int i = 0; i < MAX_OBJECTS; i++) {
        objects[i].active = false;
    }
}

// ============================================================
// 20. FUNGSI update()
// ============================================================

void update(int value) {

    if (!gameOver) {

        // ----------------------------------------------------
        // A. ANIMASI GARIS BIRU MUDA
        // ----------------------------------------------------

        // Menggeser garis ke kiri secara bertahap.
        roadOffset += roadSpeed;

        // Mengulang posisi garis agar animasi terus berjalan.
        if (roadOffset >= 100.0f) {
            roadOffset = 0.0f;
        }

        // ----------------------------------------------------
        // B. GERAKAN LOMPAT ASTRONAUT
        // ----------------------------------------------------

        if (jumping) {

            playerY += jumpVelocity;

            jumpVelocity -= GRAVITY;

            if (playerY <= 100) {

                playerY = 100;

                jumpVelocity = 0;

                jumping = false;
            }
        }

        // ----------------------------------------------------
        // C. MENGATUR KEMUNCULAN BINTANG
        // ----------------------------------------------------

        spawnTimer++;

        if (spawnTimer >= 35) {

            spawnObject();

            spawnTimer = 0;
        }

        // ----------------------------------------------------
        // D. MENGGERAKKAN DAN MEMERIKSA COLLISION BINTANG
        // ----------------------------------------------------

        for (int i = 0; i < MAX_OBJECTS; i++) {

            if (!objects[i].active)
                continue;

            // Bintang bergerak dari kanan ke kiri.
            objects[i].x -= objects[i].speed;

            // Menentukan titik tengah astronaut.
            float playerCenterX;
            float playerCenterY;

            if (crouching && !jumping) {

                playerCenterX = playerX + 42;
                playerCenterY = playerY + 35;
            }
            else {

                playerCenterX = playerX + 35;
                playerCenterY = playerY + 65;
            }

            // Mengecek tabrakan bintang dengan astronaut.
            if (collision(
                playerCenterX,
                playerCenterY,
                objects[i].x,
                objects[i].y,
                40
            )) {

                // Menambah skor 10 poin.
                score += 10;

                // Menghilangkan bintang yang tertangkap.
                objects[i].active = false;

                continue;
            }

            // Menghilangkan bintang jika keluar layar.
            if (objects[i].x < -30) {
                objects[i].active = false;
            }
        }

        // ----------------------------------------------------
        // E. MENGATUR TIMER PERMAINAN
        // ----------------------------------------------------

        gameTimer++;

        if (gameTimer >= 63) {

            timeLeft--;

            gameTimer = 0;
        }

        // ----------------------------------------------------
        // F. KONDISI GAME OVER
        // ----------------------------------------------------

        if (timeLeft <= 0) {
            gameOver = true;
        }
    }

    glutPostRedisplay();

    glutTimerFunc(16, update, 0);
}

// ============================================================
// 21. FUNGSI keyboardDown()
// ============================================================

void keyboardDown(unsigned char key, int x, int y) {

    // SPACE untuk melompat.
    if (key == ' ' && !gameOver && !jumping) {

        jumping = true;

        jumpVelocity = JUMP_POWER;

        crouching = false;
    }

    // S untuk menunduk.
    if ((key == 's' || key == 'S') &&
        !gameOver && !jumping) {

        crouching = true;
    }

    // R untuk restart.
    if ((key == 'r' || key == 'R') && gameOver) {
        resetGame();
    }

    // ESC untuk keluar.
    if (key == 27) {
        exit(0);
    }
}

// ============================================================
// 22. FUNGSI keyboardUp()
// ============================================================

void keyboardUp(unsigned char key, int x, int y) {

    if (key == 's' || key == 'S') {
        crouching = false;
    }
}

// ============================================================
// 23. FUNGSI specialDown()
// ============================================================

void specialDown(int key, int x, int y) {

    if (key == GLUT_KEY_DOWN && !gameOver && !jumping) {
        crouching = true;
    }
}

// ============================================================
// 24. FUNGSI specialUp()
// ============================================================

void specialUp(int key, int x, int y) {

    if (key == GLUT_KEY_DOWN) {
        crouching = false;
    }
}

// ============================================================
// 25. FUNGSI init()
// ============================================================

void init() {

    glClearColor(0, 0, 0, 1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(
        0, WIDTH,
        0, HEIGHT
    );

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Mengacak posisi bintang dekorasi.
    for (int i = 0; i < TOTAL_STARS; i++) {

        bgStarX[i] = rand() % WIDTH;
        bgStarY[i] = rand() % HEIGHT;
    }

    // Menonaktifkan seluruh bintang permainan.
    for (int i = 0; i < MAX_OBJECTS; i++) {
        objects[i].active = false;
    }
}

// ============================================================
// 26. FUNGSI main()
// ============================================================

int main(int argc, char** argv) {

    srand(time(NULL));

    glutInit(&argc, argv);

    glutInitDisplayMode(
        GLUT_DOUBLE | GLUT_RGB
    );

    glutInitWindowSize(
        WIDTH, HEIGHT
    );

    glutInitWindowPosition(
        100, 50
    );

    glutCreateWindow(
        "SPACE CATCHER - OPENGL"
    );

    init();

    glutDisplayFunc(display);

    glutKeyboardFunc(keyboardDown);
    glutKeyboardUpFunc(keyboardUp);

    glutSpecialFunc(specialDown);
    glutSpecialUpFunc(specialUp);

    glutTimerFunc(16, update, 0);

    glutMainLoop();

    return 0;
}
