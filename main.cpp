#include "Image.h"
#include <string>
#include <iostream>

using namespace std;

int main() {

    Image copy(0 , 0);
    string fileName {};
    cin >> fileName;
    copy.Read(fileName);
    copy.Export("image.bmp");
    copy.ExportHighContrast("contrast.bmp");
    copy.ExportWhite("hollow.bmp");

    return 0;

}