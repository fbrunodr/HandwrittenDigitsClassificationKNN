//
// Created by fbrunodr on 19/08/20.
//

#include "ImageData.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// Constructors
ImageData::ImageData() {
    this->label = -1;
    this->rows = 0;
    this->cols = 0;
    vector<int> defaultVec;
    this->image = defaultVec;
}

ImageData::ImageData(int label, const vector<int> &image, int rows, int collumns) {
    this->label = label;
    this->rows = rows;
    this->cols = collumns;
    this->image = image;
}

// Get properties
int ImageData::getLabel() {
    return label;
}

vector<int> ImageData::getImageVector() {
    return image;
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

void ImageData::print(){
    char* pixels = new char[rows * cols];

    for(int i = 0; i < rows * cols; i++)
        pixels[i] = char( image[i] ); 

    // convert it to cv Mat, and show it
    cv::Mat image_tmp(rows,cols,CV_8UC1,pixels);
    // resize bigger for showing
    cv::resize(image_tmp, image_tmp, cv::Size(rows * 10, cols * 10) );
    cv::imshow(to_string(label), image_tmp);
    cv::waitKey(0);
}
