#include "parallelMergeSort.hpp"
#include <algorithm>
#include <thread> 
#include <iostream>

ParallelMergeSort::ParallelMergeSort(std::vector<int> *nums){
    this->nums = nums;
}

// ParallelMergeSort::ParallelMergeSort(std::vector<int> *nums):nums(nums){}

ParallelMergeSort::~ParallelMergeSort(){
    delete this->nums;
}

void ParallelMergeSort::recursiveSort(int left, int right){
    const int THRESHOLD = 5000;

    if (right - left < THRESHOLD) {
        std::sort(nums->begin() + left, nums->begin() + right + 1);
        return;
    }

    int mid = left + (right - left) / 2;

    std::thread t1([this, left, mid] {this->recursiveSort(left, mid);});
    std::thread t2([this, mid, right] {this->recursiveSort(mid + 1, right);});
    t1.join();
    t2.join();
    // no need for mutex here, both access different memory locations

    std::vector<int> result;
    int i = left;
    int j = mid + 1;

    while(i<=mid && j<=right){
        if((*nums)[i] <= (*nums)[j]){
            result.push_back((*nums)[i]);
            i++;
        }else{
            result.push_back((*nums)[j]);
            j++;
        }
    }

    while(i<=mid){
        result.push_back((*nums)[i]);
        i++;
    }

    while(j<=right){
        result.push_back((*nums)[j]);
        j++;
    }

    for(int k=0; k<result.size(); k++){
        (*nums)[left + k] = result[k];
    }
}

void ParallelMergeSort::sort(){
    if((*nums).size() == 0){
        // return;
        exit(1);
    }
    recursiveSort(0, (*nums).size() - 1); // need not to spin a thread over there!!
    // std::thread thread_1([this] { this->recursiveSort(0, (*nums).size() - 1); });
    // thread_1.join();
}