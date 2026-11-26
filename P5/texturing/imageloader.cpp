#include <fstream>
#include <iostream>
#include <cstdlib>
#include "imageloader.h"

using namespace std;

Image::Image(char* ps, int w, int h)
    : pixels(ps), width(w), height(h) {}

Image::~Image() {
    delete[] pixels;
}

static unsigned int readU16(ifstream& in) {
    unsigned char b[2];
    in.read(reinterpret_cast<char*>(b), 2);
    return b[0] | (static_cast<unsigned int>(b[1]) << 8);
}

static unsigned int readU32(ifstream& in) {
    unsigned char b[4];
    in.read(reinterpret_cast<char*>(b), 4);
    return b[0]
        | (static_cast<unsigned int>(b[1]) << 8)
        | (static_cast<unsigned int>(b[2]) << 16)
        | (static_cast<unsigned int>(b[3]) << 24);
}

Image* loadBMP(const char* filename) {
    ifstream input(filename, ios::binary);

    if (!input) {
        cerr << "Gagal membuka file: " << filename << endl;
        exit(EXIT_FAILURE);
    }

    char signature[2];
    input.read(signature, 2);

    if (signature[0] != 'B' || signature[1] != 'M') {
        cerr << "File bukan BMP yang valid." << endl;
        exit(EXIT_FAILURE);
    }

    input.seekg(10);
    unsigned int dataOffset = readU32(input);

    unsigned int headerSize = readU32(input);

    if (headerSize < 40) {
        cerr << "Format header BMP tidak didukung." << endl;
        exit(EXIT_FAILURE);
    }

    int width = static_cast<int>(readU32(input));
    int height = static_cast<int>(readU32(input));

    unsigned int planes = readU16(input);
    unsigned int bitsPerPixel = readU16(input);
    unsigned int compression = readU32(input);

    if (width <= 0 || height == 0 ||
        planes != 1 || bitsPerPixel != 24 ||
        compression != 0) {
        cerr << "BMP harus 24-bit, tidak terkompresi." << endl;
        exit(EXIT_FAILURE);
    }

    input.seekg(18 + 4 + 4 + 2 + 2 + 4);
    // Kembali ke awal data setelah membaca informasi format.
    input.seekg(dataOffset);

    int actualHeight = (height < 0) ? -height : height;
    int rowSize = (width * 3 + 3) & ~3;

    char* pixels = new char[width * actualHeight * 3];
    char* row = new char[rowSize];

    for (int y = 0; y < actualHeight; ++y) {
        input.read(row, rowSize);

        if (!input) {
            delete[] row;
            delete[] pixels;
            cerr << "Data gambar BMP tidak lengkap." << endl;
            exit(EXIT_FAILURE);
        }

        int destY = (height > 0)
            ? actualHeight - 1 - y
            : y;

        for (int x = 0; x < width; ++x) {
            int src = x * 3;
            int dest = (destY * width + x) * 3;

            // BMP menyimpan warna BGR, OpenGL memakai RGB.
            pixels[dest]     = row[src + 2];
            pixels[dest + 1] = row[src + 1];
            pixels[dest + 2] = row[src];
        }
    }

    delete[] row;
    input.close();

    cout << "Berhasil memuat " << filename << endl;
    return new Image(pixels, width, actualHeight);
}