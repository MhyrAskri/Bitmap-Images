#include <vector>
#include <string>

#ifndef Bitmap_IMAGE_H
#define Bitmap_IMAGE_H

struct Color {

    float r , g , b;

    Color();
    Color(float r , float g , float b);
    ~Color();

};


class Image {

public:

    Image(int width , int height);
    ~Image();

    Color GetColor(int x , int y) const;
    void Export(const char *path) const;
    void ExportHighContrast(const char *path) const;
    void ExportWhite(const char *path) const;
    void Read(std::string path);

private:

    int mWidth , mHeight;
    std::vector<Color> mColors;

};


#endif //Bitmap_IMAGE_H
