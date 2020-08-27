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

void ImageData::print(){
    int dim = sqrt( this->image.size() );

    char* pixels = new char[dim * dim];

    for(int i = 0; i < dim * dim; i++)
        pixels[i] = char( this->image[i] ); 

    // convert it to cv Mat, and show it
    cv::Mat image_tmp(dim,dim,CV_8UC1,pixels);
    // resize bigger for showing
    cv::resize(image_tmp, image_tmp, cv::Size(300, 300));
    cv::imshow(to_string(this->label), image_tmp);
    cv::waitKey(0);
}
