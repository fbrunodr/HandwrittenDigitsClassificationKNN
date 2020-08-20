#include <iostream>
#include <queue>
#include <algorithm>
#include "readData.h"

using namespace std;

struct labelDistPair{
    int label;
    double distanceSquared;

    bool operator()(const labelDistPair& lhs, const labelDistPair& rhs){
        return lhs.distanceSquared < rhs.distanceSquared;
    }
};



int main() {
    vector<ImageData> training, test;
    training = read_mnist("../../Data/train-images-idx3-ubyte", "../../Data/train-labels-idx1-ubyte");
    test = read_mnist("../../Data/t10k-images-idx3-ubyte", "../../Data/t10k-labels-idx1-ubyte");

    if( training.size() == 0 || test.size() == 0 )
        return -1;

    // K-nearest neighborhoods code
    int K = 3;

    int numOfErrors = 0;

    for(int i = 0; i < test.size(); i++){
        // Saves the K closest training images to test image[i]
        // The farthest one stays on top of the heap (priority queue) so when a
        // closer image is found it replaces that most distant image in the heap
        priority_queue<labelDistPair, vector<labelDistPair>, labelDistPair > kClosests;

        // Start by filling the heap with K label-distance pairs with big distances
        labelDistPair initialVal; initialVal.label = -1; initialVal.distanceSquared = pow(10,8);
        for(int j = 0; j < K; j++)
            kClosests.push(initialVal);

        // Whenever a training image is closer than the farthest
        // image in the heap, it replaces that farther image
        for(int j = 0; j < training.size(); j++){
            double ijDistanceSq = test[i].distanceSquared( training[j] );
            if( ijDistanceSq < kClosests.top().distanceSquared ){
                kClosests.pop();
                labelDistPair newLDpair;
                newLDpair.label = training[j].getLabel();
                newLDpair.distanceSquared = ijDistanceSq;
                kClosests.push(newLDpair);
            }
        }


        // After getting the K closest training images to test image[i] we
        // evaluate the label that repeats the most. If there are two or
        // more tied labels, the one with a closer image is chosen.
        int digits[10];
        for(int j = 0; j < 10; j++) digits[j] = 0;

        int max = 0;
        int predicted = -1;
        for(int j = 0; j < K; j++){
            digits[ kClosests.top().label ]++;

            if( digits[ kClosests.top().label ] >= max ){
                max = digits[ kClosests.top().label ];
                predicted = kClosests.top().label;
            }

            kClosests.pop();
        }


        if( test[i].getLabel() != predicted )
            numOfErrors++;

        cout << 100 * double( numOfErrors )/ i << '%' << endl;
    }

    // Print the percentage of wrong predictions
    cout << 100 * double(numOfErrors) / test.size() << '%' << endl;

    return 0;
}