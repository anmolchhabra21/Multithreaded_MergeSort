#include <iostream>
#include "sorting/mergeSort.hpp"
#include <chrono>
#include "sorting/parallelMergeSort.hpp"

int main(int argc, char* argv[]){

    const int SIZE = 10000000;
    std::vector<int> nums(SIZE);
    std::vector<int> nums2(SIZE);

    for(int i=0; i<SIZE; i++){
        nums[i] = rand()%SIZE;
        nums2[i] = nums[i];
    }

    MergeSort mergeSort(&nums);
    auto start = std::chrono::high_resolution_clock::now();
    mergeSort.sort();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> mergesortDuration = end-start;
    std::cout<<"MergeSort with "<<SIZE<<" elements took: "<<mergesortDuration.count()<<" seconds"<<std::endl;
    // delete &mergeSort; // No need to delete stack-allocated mergeSort

    ParallelMergeSort* parallelMergeSort = new ParallelMergeSort(&nums2);
    start = std::chrono::high_resolution_clock::now();
    parallelMergeSort->sort();
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> parallelMergesortDuration = end-start;
    std::cout<<"ParallelMergeSort with "<<SIZE<<" elements took: "<<parallelMergesortDuration.count()<<" seconds"<<std::endl;
    
    delete parallelMergeSort;
    
    return 0;
}