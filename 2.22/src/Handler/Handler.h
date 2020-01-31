#include <iostream>
#include <cstdlib> 
#include <algorithm> 
#include <cctype>
#include <queue> 
#include "../AdjacencyList/AdjacencyList.h"

using namespace std;

struct Sheet
{
    int vertex;
    int vertexNumber;
};

class Handler
{
public:

    Handler(string fileName)
    {
        fstream file(fileName);
        AdjacencyList adjacencyListObject(file);
        Handler::adjacencyListObject = adjacencyListObject;
        adjacencyList = adjacencyListObject.getAdjacencyList();
        quantityOfVertex = adjacencyListObject.getQuantityOfVertex();
        initQueue();
        
        file.close();
    }

    void test2()
    {
        
    }

    void test()
    {
        for (size_t i = 1; i <= quantityOfVertex; i++)
        {
            for (size_t j = 0; j < adjacencyList[i].vertexes.size(); j++)
            {
                cout << adjacencyList[i].vertexes[j];
            }
            cout << ' ' << adjacencyList[i].quantity << endl;
        }
    }

    int getShortestWay()
    {
        int currVertexNumber;
        while (!Queue.empty()) 
        {
            for (size_t i = 1; i <= Queue.size() + 1; i++)
            {
                currVertexNumber = Queue.front();
                Queue.pop();

                if (adjacencyList[currVertexNumber].quantity == 0)
                {
                    return currVertexNumber;
                }
                
                if (!isSheet(adjacencyList[currVertexNumber].quantity))
                {
                    Queue.push(currVertexNumber);
                }
                else
                {
                    Sheet sheet;
                    sheet.vertexNumber = currVertexNumber;
                    sheet.vertex = adjacencyList[currVertexNumber].vertexes[0];

                    listOfSheets.push_back(sheet);
                }
            }
            excludeSheets();
        }

         return currVertexNumber;
    }

private:
    AdjacencyList adjacencyListObject;
    map<int, VertexData> adjacencyList;
    vector<Sheet> listOfSheets;
    int quantityOfVertex;
    queue<int> Queue;
    map<int, VertexData>::iterator cur, end;

    void excludeSheets()
    {
        for (Sheet sheet : listOfSheets)
        {
            adjacencyList[sheet.vertexNumber].vertexes.erase(sheet.vertex);
            adjacencyList[sheet.vertex].quantity--;
        }
        listOfSheets.clear();
    }

    bool isSheet(int quantity)
    {
        if (quantity == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void initQueue()
    {
        for (size_t i = 1; i <= quantityOfVertex; i++)
        {
            Queue.push(i);
        }
    }
};