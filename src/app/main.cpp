#include <iostream>
#include "sorting/mergeSort.hpp"
#include <chrono>

int main(int argc, char* argv[]){

    const int SIZE = 1000;
    std::vector<int> nums(SIZE);

    for(int i=0; i<SIZE; i++){
        nums[i] = rand()%SIZE;
    }

    MergeSort mergeSort(&nums);
    auto start = std::chrono::high_resolution_clock::now();
    mergeSort.sort();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> mergesortDuration = end-start;
    std::cout<<"MergeSort took: "<<mergesortDuration.count()<<" seconds"<<std::endl;
    
    return 0;
}