#include "../include/geographic_network.h"
#include <queue>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits>
#include <climits>
#include <functional>

GeographicNetwork::GeographicNetwork() = default;

GeographicNetwork::GeographicNetwork(GeographicNetwork &&other) noexcept : adjList(std::move(other.adjList)) {}
GeographicNetwork &GeographicNetwork::operator=(GeographicNetwork &&other) noexcept
{
    if (this != &other)
    {
        this->adjList.clear(); // Free our own resources first
        this->adjList = other.adjList;
        other.adjList.clear();
    }
    return *this;
}

// --- Vertex Management ---
void GeographicNetwork::addVertex(int node)
{
    if (this->adjList.find(node) == this->adjList.end())
    {
        this->adjList[node];
    }
}

void GeographicNetwork::removeVertex(int node)
{
    if (this->adjList.find(node) != this->adjList.end())
    {
        for (auto it : this->adjList)
        {
            for (auto i : it.second)
            {
                if (i.to == node)
                {
                    this->removeEdge(it.first, i.to);
                }
            }
        }
        this->adjList.erase(node);
    }
}

// --- Edge Management ---
void GeographicNetwork::addEdge(int from, int to, int weight)
{
    if (!this->hasEdge(from, to) && !this->hasEdge(to, from) && this->adjList.find(from) != this->adjList.end() && this->adjList.find(to) != this->adjList.end())
    {
        Edge ed1;
        ed1.to = to;
        ed1.weight = weight;
        this->adjList[from].push_back(ed1);
        Edge ed2;
        ed2.to = from;
        ed2.weight = weight;
        this->adjList[to].push_back(ed2);
    }
}

void GeographicNetwork::removeEdge(int from, int to)
{
    if (this->adjList.find(from) != this->adjList.end() && this->adjList.find(to) != this->adjList.end())
    {
        for (size_t i = 0; i < this->adjList[from].size(); i++)
        {
            if (this->adjList[from][i].to == to)
            {
                if (this->adjList[from].size() <= 1)
                {
                    this->adjList[from].pop_back();
                    return;
                }
                for (size_t j = i; j < this->adjList[from].size() - 1; j++)
                {
                    this->adjList[from][j] = this->adjList[from][j + 1];
                }
                this->adjList[from].pop_back();
                return;
            }
        }
        for (size_t i = 0; i < this->adjList[to].size(); i++)
        {
            if (this->adjList[to][i].to == from)
            {
                if (this->adjList[to].size() <= 1)
                {
                    this->adjList[to].pop_back();
                    return;
                }
                for (size_t j = i; j < this->adjList[to].size() - 1; j++)
                {
                    this->adjList[to][j] = this->adjList[to][j + 1];
                }
                this->adjList[to].pop_back();
                return;
            }
        }
    }
}

// --- Graph Queries ---
bool GeographicNetwork::hasEdge(int from, int to) const
{
    if (this->adjList.find(from) != this->adjList.end() && this->adjList.find(to) != this->adjList.end())
    {
        bool flag1 = false;
        bool flag2 = false;
        for (size_t i = 0; i < this->adjList.at(from).size(); i++)
        {
            if (this->adjList.at(from)[i].to == to)
            {
                flag1 = true;
            }
        }
        for (size_t i = 0; i < this->adjList.at(to).size(); i++)
        {
            if (this->adjList.at(to)[i].to == from)
            {
                flag2 = true;
            }
        }
        if(flag1 && flag2)
        {
            return true;
        }
    }
    return false;
}

std::vector<int> GeographicNetwork::getAdjacent(int from) const
{
    if (this->adjList.find(from) != this->adjList.end())
    {
        std::vector<int> adj;
        for(auto it : this->adjList.at(from))
        {
            adj.push_back(it.to);
        }
        return adj;
    }
    return {};
}

// --- Core Algorithm: Dijkstra's ---
std::optional<std::vector<int>> GeographicNetwork::findShortestPath(int start, int end) const
{
    if (this->adjList.find(start) == this->adjList.end() || this->adjList.find(end) == this->adjList.end())
    {
        return {};
    }

    std::unordered_map<int, std::pair<int, std::vector<int>>> Dist;
    std::priority_queue<std::pair<int, std::pair<int, std::vector<int>>>, std::vector<std::pair<int, std::pair<int, std::vector<int>>>>, std::greater<>> pq;

    for(size_t i = 1; i <= this->adjList.size() ; i++)
    {
        Dist[i].first = INT_MAX;
    }

    pq.push({0, {start, {start}}});
    Dist[start] = {0, {start}};

    while(!pq.empty())
    {
        int node = pq.top().second.first;
        int d = pq.top().first;
        std::vector<int> p = pq.top().second.second;
        pq.pop();

        for(auto it : this->adjList.at(node))
        {
            if(d + it.weight < Dist[it.to].first)
            {
                Dist[it.to].first = d + it.weight;
                std::vector<int> temp = p;
                temp.push_back(it.to);
                Dist[it.to].second = temp;

                pq.push({d + it.weight, {it.to, {temp}}});
            }
        }
    }
    if(Dist[end].second.empty())
    {
        return std::nullopt;
    }
    else
    {
        return Dist[end].second;
    }
}

// --- Core Algorithm: Kruskal's for MST ---
std::vector<GeographicNetwork::MstEdge> GeographicNetwork::calculateMinimumSpanningTree() const
{
    // TODO
    return {};
}

// --- Implementations of Advanced Analysis Functions ---

std::vector<int> GeographicNetwork::findCriticalNodes() const
{
    // TODO
    return {};
}

void GeographicNetwork::findAP_dfs(int u, int &time, std::unordered_map<int, int> &parent, std::unordered_map<int, int> &disc, std::unordered_map<int, int> &low, std::vector<int> &result) const
{
    // TODO
    // This is a helper for find critical nodes, you do not need to write this if you wont be following this certain implimentation
}

std::optional<std::vector<int>> GeographicNetwork::findPathWithMinEffort(int start, int end) const
{
    // TODO
    return {};
}
int GeographicNetwork::findBestCity(int distanceThreshold) const
{
    // TODO
    return -1;
}