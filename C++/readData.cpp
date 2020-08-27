//
// Created by fbrunodr on 19/08/20.
//

// Code adapted from https://www.thetopsites.net/article/52406407.shtml

#include "readData.h"
#include <iostream>

using namespace std;

uint32_t swap_endian(uint32_t val) {
    val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
    return (val << 16) | (val >> 16);
}

vector<ImageData> read_mnist(const char* image_filename, const char* label_filename){

    vector<ImageData> processedData(0);

    // Open files
    ifstream image_file(image_filename, ios::in | ios::binary);
    ifstream label_file(label_filename, ios::in | ios::binary);

    // Read the magic and the meta data
    uint32_t magic;
    uint32_t num_items;
    uint32_t num_labels;
    uint32_t rows;
    uint32_t cols;

    image_file.read(reinterpret_cast<char*>(&magic), 4);
    magic = swap_endian(magic);
    if(magic != 2051){
        cout<<"Incorrect image file magic: "<<magic<<endl;
        return processedData;
    }

    label_file.read(reinterpret_cast<char*>(&magic), 4);
    magic = swap_endian(magic);
    if(magic != 2049){
        cout<<"Incorrect image file magic: "<<magic<<endl;
        return processedData;
    }

    image_file.read(reinterpret_cast<char*>(&num_items), 4);
    num_items = swap_endian(num_items);
    label_file.read(reinterpret_cast<char*>(&num_labels), 4);
    num_labels = swap_endian(num_labels);
    if(num_items != num_labels){
        cout<<"image file nums should equal to label num"<<endl;
        return processedData;
    }

    image_file.read(reinterpret_cast<char*>(&rows), 4);
    rows = swap_endian(rows);
    image_file.read(reinterpret_cast<char*>(&cols), 4);
    cols = swap_endian(cols);

    char label;
    char* pixels = new char[rows * cols];

    for (int item_id = 0; item_id < num_items; ++item_id) {
        // read image pixel
        image_file.read(pixels, rows * cols);
        // read label
        label_file.read(&label, 1);

        int intLabel = int(label);
        vector<int> intPixels(rows * cols);

        for(int i = 0; i < rows*cols; i++){
            intPixels[i] = int( pixels[i] );
            if( intPixels[i] < 0 )
                intPixels[i] += 256;
        }

        processedData.push_back( ImageData(intLabel, intPixels, rows, cols) );
    }

    delete[] pixels;

    return processedData;
}
