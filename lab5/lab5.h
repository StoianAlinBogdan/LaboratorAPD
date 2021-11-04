#include <vector>

#define NODES 9

int* getIndex(std::vector<int>* adiacenta)
{
    std::vector<int> temp;
    int* index = new int[NODES];
    index[0] = adiacenta[0].size();
    for(int i = 1; i < NODES; i++)
    {
        index[i] = index[i-1] + adiacenta[i].size();
    }
    temp.clear();
    return index;
}

int * getEdges(std::vector<int>* adiacenta)
{
    std::vector<int> temp;
    for(int i = 0; i < NODES; i++)
    {
        for(int j = 0; j < adiacenta[i].size(); j++)
        {
            temp.push_back(adiacenta[i][j]);
        }
    }
    int* edges = new int[temp.size()];
    std::copy(temp.begin(), temp.end(), edges);
    temp.clear();
    return edges;
}