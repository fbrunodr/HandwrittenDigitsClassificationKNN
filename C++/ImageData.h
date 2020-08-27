//
// Created by fbrunodr on 19/08/20.
//

#ifndef DIGITSCLASSIFICATION_IMAGEDATA_H
#define DIGITSCLASSIFICATION_IMAGEDATA_H

#include <vector>
#include <cmath>
using namespace std;

class ImageData {
private:
    int label;          // The correct digit associated with the image
    vector<int> image;  // Vector containing each pixel value (from 0 to 255) in order

public:
    // Constructors
    ImageData();
    ImageData(int label, const vector<int>& image);

    // Return its properties
    int getLabel();
    vector<int> getImageVector();

    // Comparison Function
    double distanceSquared(const ImageData& otherImg);

    // Print Image
    void print();
};


#endif //DIGITSCLASSIFICATION_IMAGEDATA_H

