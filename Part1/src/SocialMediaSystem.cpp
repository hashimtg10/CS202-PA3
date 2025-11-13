#include "SocialMediaSystem.h"

SocialMediaSystem::SocialMediaSystem()
    : feed(10)  // initial capacity
{
}

int SocialMediaSystem::findPostIndex(int value) {
    for (int i = 0; i < this->feed.size(); i++)
    {
        if(this->feed.elementAt(i) == value)
        {
            return i;
        }
    }
    return -1;
}

void SocialMediaSystem::buildUndiscoveredFeed(vector<int> likes) 
{
    if(likes.empty())
    {
        return;
    }
    for(auto like : likes)
    {
        this->feed.insertKey(like);
    }
}

void SocialMediaSystem::updatePostLikes(int oldLikes, int newLikes) {
    for(int index = 0; index < this->feed.size(); index++)
    {
        if(this->feed.elementAt(index) == oldLikes)
        {
            this->feed.increaseKey(index, newLikes);
            return;
        }
    }
    
}

void SocialMediaSystem::clearLowEngagementPosts(int threshold) 
{
    while(this->feed.size() > 0 && this->feed.getMin() < threshold)
    {
        this->feed.extractMin();
    }    
}

vector<int> SocialMediaSystem::getTopNPosts(int N) {
    vector<int> allItems;
    MinHeap temp_heap = this->feed;
    while (temp_heap.size() > 0 && N > 0)
    {
        allItems.push_back(temp_heap.extractMin());
        N--;
    }
    return allItems;
}

void SocialMediaSystem::decreasePostLikes(int currentLikes, int newLikes) 
{
    int index = 0;
    for(index = 0; index < this->feed.size(); index++)
    {
        if(this->feed.elementAt(index) == currentLikes)
        {
            break;
        }
    }
    this->feed.decreaseKey(index, newLikes);
}
