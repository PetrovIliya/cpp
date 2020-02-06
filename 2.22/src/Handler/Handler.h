#include <iostream>
#include <cstdlib> 
#include <algorithm> 
#include <cctype>
#include <queue> 
#include "../AdjacencyList/AdjacencyList.h"

using namespace std;

class Handler
{
public:

    Handler(string fileName)
    {
        fstream file(fileName);
        if (!file.is_open())
        {
            cout << "no input file!";
            throw exception();
        }
        AdjacencyList adjacencyListObject(file);
        adjacencyList = adjacencyListObject.getAdjacencyList();
        quantityOfVertex = adjacencyListObject.getQuantityOfVertex();
        Handler::Queue = adjacencyListObject.getQueueOfSheets();
        cout << "Data initialized" << '\n';

        file.close();
    }

    vector<int> getShortestWay()
    {
        cout << "Searching..." << '\n';
        int count = 0;
        int currVertexNumber = 0;
        int adjencyVertex;
        while (quantityOfVertex > 2 && count < quantityOfVertex - 2) 
        {
            count++;
            currVertexNumber = Queue.front();
            Queue.pop();

            for (int j = 0; j < adjacencyList[currVertexNumber].vertexes.size(); j++)
            {
                if (adjacencyList[currVertexNumber].vertexes[j] != -1)
                {
                    adjencyVertex =  adjacencyList[currVertexNumber].vertexes[j];
                    break;
                }    
            }

            excludeSheet(currVertexNumber, adjencyVertex);
            adjacencyList[adjencyVertex].length = adjacencyList[currVertexNumber].length + 1;
                        
            if (isSheet(adjacencyList[adjencyVertex].quantity))
            {
                Queue.push(adjencyVertex);
            }
        }

        int preFinalVertex =  Queue.front();
        Queue.pop();
        int finalVertex = Queue.front();
        int tempLength = adjacencyList[preFinalVertex].length;
        adjacencyList[preFinalVertex].length = adjacencyList[finalVertex].length + 1;
        adjacencyList[finalVertex].length = tempLength + 1;

        if (adjacencyList[finalVertex].length  ==  adjacencyList[preFinalVertex].length)
        {
            return {preFinalVertex, finalVertex};
        }
        else if (adjacencyList[finalVertex].length  <  adjacencyList[preFinalVertex].length)
        {
            return {finalVertex};
        }
        else
        {
           return {preFinalVertex};
        }               
    }

private:
    map<int, VertexData> adjacencyList;
    vector <int> finalVertexes;
    int quantityOfVertex;
    queue<int> Queue;
    map<int, VertexData>::iterator cur, end;

    void excludeSheet(int vertex, int adjencyVertex)
    {     
        adjacencyList[adjencyVertex].quantity--;
        int indexOfSheet = adjacencyList[adjencyVertex].vertexesPtrs[vertex];
        adjacencyList[adjencyVertex].vertexes[indexOfSheet] = -1;
    }

    bool isSheet(int quantity)
    {
        return quantity == 1;
    }

    bool isUsed(int quantity)
    {
        return quantity == 0;
    }
};