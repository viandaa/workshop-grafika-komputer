
#include <GL/glut.h>
#include <iostream>
#include <cstdlib>
#include "imageloader.h"

using namespace std;

GLuint _textureId = 0;
float z_pos = -10.0f;
int mode = 8;

GLuint loadTexture(Image* image) {
    GLuint textureId;

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MIN_FILTER,
        GL_NEAREST
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MAG_FILTER,
        GL_NEAREST
    );

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        image->width,
        image->height,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        image->pixels
    );

    return textureId;
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    Image* image = loadBMP("ufo.bmp");
    _textureId = loadTexture(image);
    delete image;
}

void mydisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId);

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MIN_FILTER,
        GL_NEAREST
    );

    glTranslatef(0.0f, 0.0f, z_pos);

    glBegin(GL_QUADS);

    if (mode == 8) {
        // Langkah 8: texture utuh
        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(-2.0f, -2.0f);

        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(2.0f, -2.0f);

        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(2.0f, 2.0f);

        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(-2.0f, 2.0f);
    }
    else if (mode == 9) {
        // Langkah 9: texture diputar 90 derajat
        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(-2.0f, -2.0f);

        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(2.0f, -2.0f);

        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(2.0f, 2.0f);

        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(-2.0f, 2.0f);
    }
    else if (mode == 10) {
        // Langkah 10: sebagian texture diperbesar
        glTexCoord2f(0.4f, 0.6f);
        glVertex2f(-2.0f, -2.0f);

        glTexCoord2f(0.5f, 0.6f);
        glVertex2f(2.0f, -2.0f);

        glTexCoord2f(0.5f, 0.7f);
        glVertex2f(2.0f, 2.0f);

        glTexCoord2f(0.4f, 0.7f);
        glVertex2f(-2.0f, 2.0f);
    }

    glEnd();

    glDisable(GL_TEXTURE_2D);
    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) {
        h = 1;
    }

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(
        45.0,
        (double)w / (double)h,
        1.0,
        100.0
    );

    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    if (key == '8') {
        mode = 8;
    }
    else if (key == '9') {
        mode = 9;
    }
    else if (key == '0') {
        mode = 10;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(
        GLUT_DOUBLE |
        GLUT_RGB |
        GLUT_DEPTH
    );

    glutInitWindowSize(600, 600);
    glutCreateWindow("Material Texture");

    init();

    glutDisplayFunc(mydisplay);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
