#include "Image.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

Color::Color()
        : r(0) , g(0) , b(0) {

}

Color::Color(float r, float g, float b)
        : r(r) , g(g) , b(b) {

}

Color::~Color() = default;

Image::Image(int width, int height)
        : mWidth(width) , mHeight(height) , mColors(vector<Color>(width * height)) {

}

Image::~Image() = default;

Color Image::GetColor(int x, int y) const {

    return mColors[y * mWidth + x];

}

void Image::Export(const char *path) const {

    ofstream f;
    f.open(path , ios::out | ios::binary);

    if (!f.is_open()) {

        cout << "Error" << endl;
        return;

    }

    unsigned char bmpPad[3] = {0 , 0 , 0};
    const int paddingAmount = ((4 - (mWidth * 3) % 4) % 4);

    const int fileHeaderSize = 14;
    const int informationHeaderSize = 40;

    int fileSize = fileHeaderSize + informationHeaderSize + mWidth * mHeight * 3 + paddingAmount * mWidth;

    unsigned char fileHeader[fileHeaderSize];

    // File type
    fileHeader[0] = 'B';
    fileHeader[1] = 'M';

    // File size
    fileHeader[2] = fileSize;
    fileHeader[3] = fileSize >> 8;
    fileHeader[4] = fileSize >> 16;
    fileHeader[5] = fileSize >> 24;

    // Reserved 1 (Not used)
    fileHeader[6] = 0;
    fileHeader[7] = 0;

    // Reserved 2 (Not used)
    fileHeader[8] = 0;
    fileHeader[9] = 0;

    // Pixel data offset
    fileHeader[10] = fileHeaderSize + informationHeaderSize;
    fileHeader[11] = 0;
    fileHeader[12] = 0;
    fileHeader[13] = 0;

    unsigned char informationHeader[informationHeaderSize];

    // Header size
    informationHeader[0] = informationHeaderSize;
    informationHeader[1] = 0;
    informationHeader[2] = 0;
    informationHeader[3] = 0;

    // Image width
    informationHeader[4] = mWidth;
    informationHeader[5] = mWidth >> 8;
    informationHeader[6] = mWidth >> 16;
    informationHeader[7] = mWidth >> 24;

    // Image height
    informationHeader[8] = mHeight;
    informationHeader[9] = mHeight >> 8;
    informationHeader[10] = mHeight >> 16;
    informationHeader[11] = mHeight >> 24;

    // Plans
    informationHeader[12] = 1;
    informationHeader[13] = 0;

    // Bits per pixel
    informationHeader[14] = 24;
    informationHeader[15] = 0;

    // Compression (No Compression)
    informationHeader[16] = 0;
    informationHeader[17] = 0;
    informationHeader[18] = 0;
    informationHeader[19] = 0;

    // Image size (No Compression)
    informationHeader[20] = 0;
    informationHeader[21] = 0;
    informationHeader[22] = 0;
    informationHeader[23] = 0;

    // X pixel per meter (Not specified)
    informationHeader[24] = 0;
    informationHeader[25] = 0;
    informationHeader[26] = 0;
    informationHeader[27] = 0;

    // Y pixel per meter (Not specified)
    informationHeader[28] = 0;
    informationHeader[29] = 0;
    informationHeader[30] = 0;
    informationHeader[31] = 0;

    // Total colors (Color palette not used)
    informationHeader[32] = 0;
    informationHeader[33] = 0;
    informationHeader[34] = 0;
    informationHeader[35] = 0;

    // Important colors (Generally Ignored)
    informationHeader[36] = 0;
    informationHeader[37] = 0;
    informationHeader[38] = 0;
    informationHeader[39] = 0;

    f.write(reinterpret_cast<const char *>(fileHeader), fileHeaderSize);
    f.write(reinterpret_cast<const char *>(informationHeader), informationHeaderSize);

    for (int y = 0 ; y < mHeight ; ++y) {

        for (int x = 0 ; x < mWidth ; ++x) {

            unsigned char r = static_cast<unsigned char>(GetColor(x , y).r * 255.0f);
            unsigned char g = static_cast<unsigned char>(GetColor(x , y).g * 255.0f);
            unsigned char b = static_cast<unsigned char>(GetColor(x , y).b * 255.0f);

            unsigned char color[] = {b , g , r};

            f.write(reinterpret_cast<const char *>(color), 3);

        }

        f.write(reinterpret_cast<const char *>(bmpPad), paddingAmount);

    }

    f.close();

    cout << "File image created!" << endl;

}

void Image::ExportHighContrast(const char *path) const {

    ofstream f;
    f.open(path , ios::out | ios::binary);

    if (!f.is_open()) {

        cout << "Error" << endl;
        return;

    }

    unsigned char bmpPad[3] = {0 , 0 , 0};
    const int paddingAmount = ((4 - (mWidth * 3) % 4) % 4);

    const int fileHeaderSize = 14;
    const int informationHeaderSize = 40;

    int fileSize = fileHeaderSize + informationHeaderSize + mWidth * mHeight * 3 + paddingAmount * mWidth;

    unsigned char fileHeader[fileHeaderSize];

    // File type
    fileHeader[0] = 'B';
    fileHeader[1] = 'M';

    // File size
    fileHeader[2] = fileSize;
    fileHeader[3] = fileSize >> 8;
    fileHeader[4] = fileSize >> 16;
    fileHeader[5] = fileSize >> 24;

    // Reserved 1 (Not used)
    fileHeader[6] = 0;
    fileHeader[7] = 0;

    // Reserved 2 (Not used)
    fileHeader[8] = 0;
    fileHeader[9] = 0;

    // Pixel data offset
    fileHeader[10] = fileHeaderSize + informationHeaderSize;
    fileHeader[11] = 0;
    fileHeader[12] = 0;
    fileHeader[13] = 0;

    unsigned char informationHeader[informationHeaderSize];

    // Header size
    informationHeader[0] = informationHeaderSize;
    informationHeader[1] = 0;
    informationHeader[2] = 0;
    informationHeader[3] = 0;

    // Image width
    informationHeader[4] = mWidth;
    informationHeader[5] = mWidth >> 8;
    informationHeader[6] = mWidth >> 16;
    informationHeader[7] = mWidth >> 24;

    // Image height
    informationHeader[8] = mHeight;
    informationHeader[9] = mHeight >> 8;
    informationHeader[10] = mHeight >> 16;
    informationHeader[11] = mHeight >> 24;

    // Plans
    informationHeader[12] = 1;
    informationHeader[13] = 0;

    // Bits per pixel
    informationHeader[14] = 24;
    informationHeader[15] = 0;

    // Compression (No Compression)
    informationHeader[16] = 0;
    informationHeader[17] = 0;
    informationHeader[18] = 0;
    informationHeader[19] = 0;

    // Image size (No Compression)
    informationHeader[20] = 0;
    informationHeader[21] = 0;
    informationHeader[22] = 0;
    informationHeader[23] = 0;

    // X pixel per meter (Not specified)
    informationHeader[24] = 0;
    informationHeader[25] = 0;
    informationHeader[26] = 0;
    informationHeader[27] = 0;

    // Y pixel per meter (Not specified)
    informationHeader[28] = 0;
    informationHeader[29] = 0;
    informationHeader[30] = 0;
    informationHeader[31] = 0;

    // Total colors (Color palette not used)
    informationHeader[32] = 0;
    informationHeader[33] = 0;
    informationHeader[34] = 0;
    informationHeader[35] = 0;

    // Important colors (Generally Ignored)
    informationHeader[36] = 0;
    informationHeader[37] = 0;
    informationHeader[38] = 0;
    informationHeader[39] = 0;

    f.write(reinterpret_cast<const char *>(fileHeader), fileHeaderSize);
    f.write(reinterpret_cast<const char *>(informationHeader), informationHeaderSize);

    for (int y = 0 ; y < mHeight ; ++y) {

        for (int x = 0 ; x < mWidth ; ++x) {

            unsigned char r = static_cast<unsigned char>(GetColor(x , y).r * 255.0f);
            unsigned char g = static_cast<unsigned char>(GetColor(x , y).g * 255.0f);
            unsigned char b = static_cast<unsigned char>(GetColor(x , y).b * 255.0f);

            if ((int) (r) < 127) {

                r /= 2;

            } else {

                r = (r + 255) / 2;

            }
            if ((int) (g) < 127) {

                g /= 2;

            } else {

                g = (g + 255) / 2;

            }
            if ((int) (b) < 127) {

                b /= 2;

            } else {

                b = (b + 255) / 2;

            }

            unsigned char color[] = {b , g , r};

            f.write(reinterpret_cast<const char *>(color), 3);

        }

        f.write(reinterpret_cast<const char *>(bmpPad), paddingAmount);

    }

    f.close();

    cout << "File contrast created!" << endl;

}

void Image::ExportWhite(const char *path) const {

    ofstream f;
    f.open(path , ios::out | ios::binary);

    if (!f.is_open()) {

        cout << "Error" << endl;
        return;

    }

    unsigned char bmpPad[3] = {0 , 0 , 0};
    const int paddingAmount = ((4 - (mWidth * 3) % 4) % 4);

    const int fileHeaderSize = 14;
    const int informationHeaderSize = 40;

    int fileSize = fileHeaderSize + informationHeaderSize + mWidth * mHeight * 3 + paddingAmount * mWidth;

    unsigned char fileHeader[fileHeaderSize];

    // File type
    fileHeader[0] = 'B';
    fileHeader[1] = 'M';

    // File size
    fileHeader[2] = fileSize;
    fileHeader[3] = fileSize >> 8;
    fileHeader[4] = fileSize >> 16;
    fileHeader[5] = fileSize >> 24;

    // Reserved 1 (Not used)
    fileHeader[6] = 0;
    fileHeader[7] = 0;

    // Reserved 2 (Not used)
    fileHeader[8] = 0;
    fileHeader[9] = 0;

    // Pixel data offset
    fileHeader[10] = fileHeaderSize + informationHeaderSize;
    fileHeader[11] = 0;
    fileHeader[12] = 0;
    fileHeader[13] = 0;

    unsigned char informationHeader[informationHeaderSize];

    // Header size
    informationHeader[0] = informationHeaderSize;
    informationHeader[1] = 0;
    informationHeader[2] = 0;
    informationHeader[3] = 0;

    // Image width
    informationHeader[4] = mWidth;
    informationHeader[5] = mWidth >> 8;
    informationHeader[6] = mWidth >> 16;
    informationHeader[7] = mWidth >> 24;

    // Image height
    informationHeader[8] = mHeight;
    informationHeader[9] = mHeight >> 8;
    informationHeader[10] = mHeight >> 16;
    informationHeader[11] = mHeight >> 24;

    // Plans
    informationHeader[12] = 1;
    informationHeader[13] = 0;

    // Bits per pixel
    informationHeader[14] = 24;
    informationHeader[15] = 0;

    // Compression (No Compression)
    informationHeader[16] = 0;
    informationHeader[17] = 0;
    informationHeader[18] = 0;
    informationHeader[19] = 0;

    // Image size (No Compression)
    informationHeader[20] = 0;
    informationHeader[21] = 0;
    informationHeader[22] = 0;
    informationHeader[23] = 0;

    // X pixel per meter (Not specified)
    informationHeader[24] = 0;
    informationHeader[25] = 0;
    informationHeader[26] = 0;
    informationHeader[27] = 0;

    // Y pixel per meter (Not specified)
    informationHeader[28] = 0;
    informationHeader[29] = 0;
    informationHeader[30] = 0;
    informationHeader[31] = 0;

    // Total colors (Color palette not used)
    informationHeader[32] = 0;
    informationHeader[33] = 0;
    informationHeader[34] = 0;
    informationHeader[35] = 0;

    // Important colors (Generally Ignored)
    informationHeader[36] = 0;
    informationHeader[37] = 0;
    informationHeader[38] = 0;
    informationHeader[39] = 0;

    f.write(reinterpret_cast<const char *>(fileHeader), fileHeaderSize);
    f.write(reinterpret_cast<const char *>(informationHeader), informationHeaderSize);

    float pixel[mHeight][mWidth];

    for (int y = 0 ; y < mHeight ; ++y) {

        for (int x = 0 ; x < mWidth ; ++x) {

            pixel[y][x] = 3 * GetColor(x , y).r * 255.0f;

        }

    }

    for (int y = 0 ; y < mHeight ; ++y) {

        for (int x = 0 ; x < mWidth ; ++x) {

            unsigned char r = static_cast<unsigned char>(GetColor(x , y).r * 255.0f);
            unsigned char g = static_cast<unsigned char>(GetColor(x , y).g * 255.0f);
            unsigned char b = static_cast<unsigned char>(GetColor(x , y).b * 255.0f);

            if(pixel[y][x-1]==0 && pixel[y][x+1]==0 &&
               pixel[y+1][x-1]==0 && pixel[y+1][x]==0 &&
               pixel[y+1][x+1]==0 && pixel[y-1][x+1]==0 &&
               pixel[y-1][x]==0 && pixel[y-1][x-1]==0 ) {

                r = static_cast<unsigned char>(255);
                g = static_cast<unsigned char>(255);
                b = static_cast<unsigned char>(255);

            }

            unsigned char color[] = {b , g , r};
            f.write(reinterpret_cast<const char *>(color), 3);

        }

        f.write(reinterpret_cast<const char *>(bmpPad), paddingAmount);

    }

    f.close();

    cout << "File hollow created!" << endl;

}


void Image::Read(string path) {

    ifstream f;
    f.open(path, ios::in | ios::binary);

    if(!f.is_open()) {
        cout << "error" << endl;
        return;
    }

    const int fileHeaderSize = 14;
    const int informationHeaderSize = 40;

    unsigned char fileHeader[fileHeaderSize];
    f.read(reinterpret_cast<char *>(fileHeader) , fileHeaderSize);

    if (fileHeader[0] != 'B' || fileHeader[1] != 'M') {

        cout << "not a bitmap image" << endl;
        f.close();
        return;

    }

    unsigned char informationHeader[informationHeaderSize];
    f.read(reinterpret_cast<char *>(informationHeader) , informationHeaderSize);

    int fileSize = fileHeader[2] + (fileHeader[3] << 8) + (fileHeader[4] << 16) + (fileHeader[5] << 24);
    mWidth = informationHeader[4] + (informationHeader[5] << 8) + (informationHeader[6] << 16) + (informationHeader[7] << 24);
    mHeight = informationHeader[8] + (informationHeader[9] << 8) + (informationHeader[10] << 16) + (informationHeader[11] << 24);

    mColors.resize(mWidth * mHeight);

    const int paddingAmount = ((4 - (mWidth * 3) % 4) % 4);

    for (int y = 0 ; y < mHeight ; y++) {

        for (int x = 0 ; x < mWidth ; ++x) {

            unsigned char color[3];
            f.read(reinterpret_cast<char *>(color) , 3);

            mColors[y * mWidth + x].r = static_cast<float>(color[2]) / 255.0f;
            mColors[y * mWidth + x].g = static_cast<float>(color[1]) / 255.0f;
            mColors[y * mWidth + x].b = static_cast<float>(color[0]) / 255.0f;

        }

        f.ignore(paddingAmount);
        
    }

    f.close();

    cout << "Done" << endl;

}
