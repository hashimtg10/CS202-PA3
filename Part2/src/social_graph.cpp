#include "../include/social_graph.h"
#include <queue>
#include <algorithm>
#include <utility>
#include <vector>
#include <stack>
#include <iostream>
#include <climits>

SocialGraph::SocialGraph() = default;

SocialGraph::SocialGraph(SocialGraph &&other) noexcept
    : adjList(std::move(other.adjList))
{
}

SocialGraph &SocialGraph::operator=(SocialGraph &&other) noexcept
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

void SocialGraph::addVertex(int node)
{
    if (this->adjList.find(node) == this->adjList.end())
    {
        this->adjList[node];
    }
}

void SocialGraph::removeVertex(int node)
{
    if (this->adjList.find(node) != this->adjList.end())
    {
        for (auto it : this->adjList)
        {
            for (auto i : it.second)
            {
                if (i == node)
                {
                    this->removeEdge(it.first, i);
                }
            }
        }
        this->adjList.erase(node);
    }
}

// --- Edge Management ---

void SocialGraph::addEdge(int from, int to, int /*weight*/)
{
    if (!this->hasEdge(from, to) && this->adjList.find(from) != this->adjList.end() && this->adjList.find(to) != this->adjList.end())
    {
        this->adjList[from].push_back(to);
    }
}

void SocialGraph::removeEdge(int from, int to)
{
    if (this->adjList.find(from) != this->adjList.end() && this->adjList.find(to) != this->adjList.end())
    {
        for (size_t i = 0; i < this->adjList[from].size(); i++)
        {
            if (this->adjList[from][i] == to)
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
    }
}

// --- Graph Queries ---

bool SocialGraph::hasEdge(int from, int to) const
{
    if (this->adjList.find(from) != this->adjList.end() && this->adjList.find(to) != this->adjList.end())
    {
        for (size_t i = 0; i < this->adjList.at(from).size(); i++)
        {
            if (this->adjList.at(from)[i] == to)
            {
                return true;
            }
        }
        return false;
    }
    return false;
}

std::vector<int> SocialGraph::getAdjacent(int from) const
{
    if (this->adjList.find(from) != this->adjList.end())
    {
        return this->adjList.at(from);
    }
    return {};
}

std::optional<std::vector<int>> SocialGraph::findShortestPath(int start, int end) const
{
    if (this->adjList.find(start) == this->adjList.end() || this->adjList.find(end) == this->adjList.end())
    {
        return {};
    }

    std::vector<std::pair<int, std::vector<int>>> Dist; // this vector stores the shortest distance to a node from the start node as well as the shortest path to that node
    Dist.resize(this->adjList.size() + 1);
    for (size_t i = 0; i < Dist.size(); i++)
    {
        Dist[i].first = INT_MAX;
    }
    std::queue<std::pair<int, std::vector<int>>> q; // this queue stores the current distance to a node and the current path to that node.

    q.push({start, {start}});
    Dist[start].first = 0;
    Dist[start].second.push_back(start);

    while (!q.empty())
    {
        int node = q.front().first;
        // std::cout << std::endl << "Node: " << node << std::endl;
        std::vector<int> path = q.front().second;

        q.pop();

        for (auto it : this->adjList.at(node))
        {
            std::vector<int> temp = path;
            temp.push_back(it);

            if (int(temp.size()) - 1 < Dist[it].first)
            {
                Dist[it].first = temp.size() - 1;
                Dist[it].second = temp;
                q.push({it, temp});
            }
        }
    }
    // std::cout << std::endl;
    // for(auto it : Dist[end].second)
    // {
    //     std::cout  << it << ", ";
    // }
    // std::cout << std::endl;
    if (Dist[end].second.empty())
    {
        return std::nullopt;
    }
    else
    {

        return Dist[end].second;
    }
}

// --- Advanced Analysis Functions ---

std::vector<std::pair<int, int>> SocialGraph::findEchoChambers() const
{
    std::vector<std::pair<int, int>> pairs;
    for (size_t i = 0; i < this->adjList.size(); i++)
    {
        for (size_t j = i + 1; j <= this->adjList.size(); j++)
        {
            if (this->hasEdge(i, j) && this->hasEdge(j, i))
            {
                pairs.push_back({i, j});
            }
        }
    }
    return pairs;
}

std::unordered_map<int, double> SocialGraph::calculatePageRank(double damping, int iterations) const
{
    // Creating a map of followers for all the entities
    std::unordered_map<int, std::vector<int>> followers;
    for (size_t i = 1; i <= this->adjList.size(); i++)
    {
        for (auto j : this->adjList.at(i))
        {
            followers[j].push_back(i);
        }
    }

    // Initializing a map for the ranks for all the entities
    std::unordered_map<int, double> ranks;

    for (size_t i = 1; i <= this->adjList.size(); i++)
    {
        ranks[i] = 1.0 / double(this->adjList.size());
    }
    // Updating the ranks

    for (int i = 0; i < iterations; i++)
    {
        std::unordered_map<int, double> new_ranks;

        double sum_of_ranks_with_no_outbound = 0.0;
        for (size_t j = 1; j <= this->adjList.size(); j++)
        {
            if (this->adjList.at(j).size() == 0)
            {
                sum_of_ranks_with_no_outbound += ranks[j];
            }
        }

        double S_N = sum_of_ranks_with_no_outbound / double(this->adjList.size());

        for (size_t j = 1; j <= this->adjList.size(); j++)
        {
            double constant = (1.0 - damping) / double(this->adjList.size());
            double total_contribution = 0.0;

            for (auto it : followers[j])
            {
                double out_bound = double(this->adjList.at(it).size());
                double cont = 0.0;
                if (out_bound != 0)
                {
                    cont = ranks[it] / out_bound;
                }
                total_contribution += cont;
            }
            total_contribution += S_N;

            total_contribution *= damping;

            total_contribution += constant;

            new_ranks[j] = total_contribution;
        }

        ranks = new_ranks;
    }
    return ranks;
}

std::vector<std::vector<int>> SocialGraph::findCommunities() const
{
    // TODO
    return {};
}

void SocialGraph::kosaraju_dfs1(int u, std::unordered_map<int, bool> &visited, std::vector<int> &finish_stack) const
{
    // TODO
}

void SocialGraph::kosaraju_dfs2(int u, std::unordered_map<int, bool> &visited, std::vector<int> &component, const std::unordered_map<int, std::vector<int>> &transposed_graph) const
{
    // TODO
}