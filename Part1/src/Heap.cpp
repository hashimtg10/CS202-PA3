#include "Heap.h"
#include <iostream>
#include <climits> 

using namespace std;

MinHeap::MinHeap(int cap)
{
    this->harr = new int[cap];
    this->capacity = cap;
    this->heap_size = 0;
} 

MinHeap::~MinHeap()
{
    if(this->heap_size > 0)
    {
        delete[] this->harr;
    }
    this->capacity = 0;
    this->heap_size = 0;
}

MinHeap::MinHeap(const MinHeap& other)
{
    this->capacity = other.capacity;
    this->heap_size = other.heap_size;
    this->harr = new int[this->capacity];
    for(int i = 0; i < this->heap_size ; i++)
    {  
        this->harr[i] = other.harr[i];
    }   
}

MinHeap& MinHeap::operator=(const MinHeap& other)
{
    this->capacity = other.capacity;
    this->heap_size = other.heap_size;
    this->harr = new int[this->capacity];
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
        this->minHeapify(0); // this sends the large swapped element down.
        this->minHeapify(0); // this allows the actual minimum to come to the root.
        return min;
    }
    return INT_MAX;
}

void MinHeap::decreaseKey(int i, int new_val)
{
    if(i < this->heap_size)
    {
        this->harr[i] = new_val;
        this->minHeapify(i);
    }
}

void MinHeap::increaseKey(int i, int new_val)
{
    if(i >= 0 && i < this->heap_size)
    {
        this->harr[i] = new_val;
        this->minHeapify(i);
    }
}

int MinHeap::getMin() const
{
    if(this->heap_size > 0)
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
    if(i >= 0 && i < this->heap_size)
    {
        this->harr[i] = this->harr[this->heap_size - 1];
        this->heap_size--;
        this->minHeapify(i);
    }
}

void MinHeap::insertKey(int k)
{
    if(this->heap_size >= this->capacity)
    {
        int* new_harr = new int[this->capacity*2];
        for(int i = 0; i < this->size(); i++)
        {
            new_harr[i] = this->harr[i];
        }
        delete[] this->harr;
        this->harr = new_harr;
        this->capacity *= 2;
    }
    this->harr[this->heap_size] = k;
    this->heap_size++;
    this->minHeapify(this->heap_size - 1);
}

// void MinHeap::minHeapify(int i)
// {
//     if(i < 0 || i >= this->size())
//     {
//         return;
//     }
//     while(i >= 0 && this->harr[this->parent(i)] > this->harr[i])
//     {
//         this->swap(&this->harr[this->parent(i)], &this->harr[i]);
//         i = this->parent(i);
//     }
//     while((this->left(i) < this->size() && this->harr[this->left(i)] < this->harr[i]) || (this->right(i) < this->size() && this->harr[this->right(i)] < this->harr[i]))
//     {
//         if(this->harr[this->left(i)] < this->harr[i])
//         {
//             this->swap(&this->harr[this->left(i)], &this->harr[i]);
//             i = this->left(i);
//         }
//         else
//         {
//             this->swap(&this->harr[this->right(i)], &this->harr[i]);
//             i = this->right(i);
//         }
//     }
// }
void MinHeap::minHeapify(int i)
{
    if(i < 0 || i >= this->size())
    {
        return;
    }
    if(this->parent(i) >= 0 && this->harr[this->parent(i)] > this->harr[i])
    {
        this->swap(&this->harr[this->parent(i)], &this->harr[i]);
        this->minHeapify(this->parent(i));
    }
    if(this->left(i) < this->size() && (this->harr[this->left(i)] < this->harr[i]))
    {
        this->swap(&this->harr[this->left(i)], &this->harr[i]);
        this->minHeapify(this->left(i));
    }
    if(this->right(i) < this->size() && (this->harr[this->right(i)] < this->harr[i]))
    {
        this->swap(&this->harr[this->right(i)], &this->harr[i]);
        this->minHeapify(this->right(i));
    }
}
