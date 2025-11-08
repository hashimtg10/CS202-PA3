#include "Heap.h"
#include <iostream>
#include <climits> 

using namespace std;

MinHeap::MinHeap(int cap)
{
    this->harr = new int(cap);
    this->capacity = cap;
    this->heap_size = 0;
} 

MinHeap::~MinHeap()
{
    if(this->harr)
    {
        delete[] this->harr;
        this->capacity = 0;
        this->heap_size = 0;
    }
}

MinHeap::MinHeap(const MinHeap& other)
{
    this->capacity = other.capacity;
    this->heap_size = other.heap_size;
    this->harr = new int(this->capacity);
    for(int i = 0; i < this->heap_size ; i++)
    {  
        this->harr[i] = other.harr[i];
    }   
}

MinHeap& MinHeap::operator=(const MinHeap& other)
{
    this->capacity = other.capacity;
    this->heap_size = other.heap_size;
    this->harr = new int(this->capacity);
    for(int i = 0; i < this->heap_size ; i++)
    {  
        this->harr[i] = other.harr[i];
    }   
    return *this;
}

int MinHeap::extractMin()
{
    if(this->heap_size > 0)
    {
        int min = this->harr[0];
        this->harr[0] = this->harr[this->heap_size - 1];
        this->heap_size--;
        this->minHeapify(0);
        return min;
    }
    return -1111;
}

void MinHeap::decreaseKey(int i, int new_val)
{
    if(this->harr[i])
    {
        this->harr[i] = new_val;
        this->minHeapify(i);
    }
}

void MinHeap::increaseKey(int i, int new_val)
{
    if(this->harr[i])
    {
        this->harr[i] = new_val;
        this->minHeapify(i);
    }
}

int MinHeap::getMin() const
{
    if(this->harr[0])
    {
        return this->harr[0];
    }
    else
    {
        return -1111;
    }
}

void MinHeap::deleteKey(int i)
{
    if(i < this->heap_size)
    {
        this->harr[i] = INT_MIN;
        this->minHeapify(0);
        this->extractMin();
    }
}

void MinHeap::insertKey(int k)
{
    if(this->heap_size == this->capacity)
    {
        int* new_harr = new int(this->capacity*2);
        for(int i = 0; i < this->size(); i++)
        {
            new_harr[i] = this->harr[i];
        }
        delete this->harr;
        this->harr = new_harr;
        this->capacity *= 2;
    }
    this->harr[this->heap_size] = k;
    this->heap_size++;
}

void MinHeap::minHeapify(int i)
{
    if(this->parent(i) >=0 && this->harr[this->parent(i)] > this->harr[i])
    {
        //downward Trickling case on parent(i)
    }
    else if(this->left(i) < this->size() && this->harr[this->left(i)] < this->harr[i])
    {
        //upward Bubbling case on right(i)
    }
    else if(this->right(i) < this->size() && this->harr[this->right(i)] < this->harr[i])
    {
        //upward Bubbling case on left(i)
    }
    else
    {
        //all good
    }
}