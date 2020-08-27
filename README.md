# Handwritten Digits Classification with KNN method
C++ and Lua code for K-nearest-neighbors classification of MNIST database

In C++ code it also prints the wrong labeled images. You can turn it off by commenting the line "test\[i\].print();" in main.cpp. The class ImageData has a print function that allows to print any image in the data.

Don't forget to extract the data before running the code.
To compile the C++ code, do the following comands on terminal:

```sh
$ cd C++
$ mkdir build
$ cd build
$ cmake ..
$ make
$ ./digitsClassification_main
```

You can change the CMake version in the CMakeLists.txt file if it keeps requiring a higher version.
