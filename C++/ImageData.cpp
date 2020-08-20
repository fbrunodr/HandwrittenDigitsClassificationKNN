//
// Created by fbrunodr on 19/08/20.
//

#include "ImageData.h"

// Constructors
ImageData::ImageData() {
    this->label = -1;
    vector<int> defaultVec;
    this->image = defaultVec;
}

ImageData::ImageData(int label, const vector<int> &image) {
    this->label = label;
    this->image = image;
}

// Get properties
int ImageData::getLabel() {
    return this->label;
}

vector<int> ImageData::getImageVector() {
    return this->image;
}

// Comparison Function
double ImageData::distanceSquared(const ImageData &otherImg) {
    if( this->image.size() != otherImg.image.size() )
        return -1;

    double distance = 0;
    for(int i = 0; i < this->image.size(); i++)
        distance += pow( this->image[i] - otherImg.image[i], 2 );

    return distance;
}