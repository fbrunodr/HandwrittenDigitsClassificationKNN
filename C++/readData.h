//
// Created by fbrunodr on 19/08/20.
//

// Code adapted from https://www.thetopsites.net/article/52406407.shtml

#ifndef C___READDATA_H
#define C___READDATA_H

#include <fstream>
#include <vector>
#include "ImageData.h"

uint32_t swap_endian(uint32_t val);
vector<ImageData> read_mnist(const char* image_filename, const char* label_filename);

#endif //C___READDATA_H
