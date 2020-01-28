#include <iostream>
#include <cstdlib> 
#include <algorithm> 
#include <cctype>
#include <stack>
#include <queue> 
#include "src/AdjacencyList/AdjacencyList.h"

#define FILE_NAME "INPUT.txt"

using namespace std;

 vector<int> getLengthForEachVortexByVortex(map<int, map<int, int>> adjacencyList, int startVortex)
{
    int quantityOfVortex = adjacencyList.size();
    queue<int> Queue;
    Queue.push(startVortex); 
    vector<bool> used(quantityOfVortex, false);
    vector<int> length(quantityOfVortex);
    used[startVortex] = true;
    while (!Queue.empty()) 
    {
        int currVortex = Queue.front();
        Queue.pop();
        for (size_t i = 0; i < adjacencyList[currVortex].size(); ++i) 
        {
            int to = adjacencyList[currVortex][i];
            if (!used[to])
            {
                used[to] = true;
                Queue.push(to);
                length[to] = length[currVortex] + 1;
            }
        }
    }

    return length;
}

void write1()
{}

int main()
{
    queue<int> q;
    fstream file(FILE_NAME);
    AdjacencyList adjacencyListObject(file);
    map<int, map<int, int>> adjacencyList = adjacencyListObject.getAdjacencyList();
    int quantityOfVertex = adjacencyListObject.getQuantityOfVertex();
    vector<vector<int>> vertexAdjacency = adjacencyListObject.getVertexAdjacency();
    map<int, int> listOfMaxWays;
    vector<int> listOfWays;
    int start;

    // for (int i = 1; i <= quantityOfVertex; i++)
    // {
    //     for (int j = 0; j < adjacencyList[i].size(); j++)
    //     {
    //        cout << adjacencyList[i][j] << ' ';
    //     }
    //     cout << '\n';
    // }

     for (int i = 1; i <= quantityOfVertex; i++)
     {
        listOfWays = getLengthForEachVortexByVortex(adjacencyList, i);
        for(int list : listOfWays)
        {
            cout << list;
        }
        cout << '\n';
        listOfMaxWays[i] = *max_element(listOfWays.begin(), listOfWays.end());
        //cout << listOfMaxWays[i] << '\n';
    }

    return 0;
}