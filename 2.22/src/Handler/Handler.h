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


    vector<Sheet> getShortestWay()
    {
        int currVertexNumber;
        while (!Queue.empty()) 
        {
            listOfSheets.clear();
            for (size_t i = 1; i <= adjacencyList.size(); i++)
            {
                currVertexNumber = Queue.front();
                Queue.pop();

                if (isUsed(adjacencyList[currVertexNumber].quantity))
                {
                    listOfSheets.clear();
                    Sheet sheet;
                    sheet.vertexNumber = currVertexNumber;
                    listOfSheets.push_back(sheet);
                    
                    return listOfSheets;
                }
                
                if (!isSheet(adjacencyList[currVertexNumber].quantity))
                {
                    Queue.push(currVertexNumber);
                }
                else
                {
                    Sheet sheet;
                    sheet.vertexNumber = currVertexNumber;
                    for (int j = 0; j < adjacencyList[currVertexNumber].vertexes.size(); j++)
                    {
                        if (adjacencyList[currVertexNumber].vertexes[j] != -1)
                        {
                            sheet.vertex = adjacencyList[currVertexNumber].vertexes[j];
                            break;
                        }      
                    }
                    
                    listOfSheets.push_back(sheet);
                }
            }
            excludeSheets();
        }

         return listOfSheets;
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
            adjacencyList[sheet.vertex].quantity--;
            for (size_t i = 0; i < adjacencyList[sheet.vertex].vertexes.size(); i++)
            {
                if (adjacencyList[sheet.vertex].vertexes[i] == sheet.vertexNumber)
                {
                    adjacencyList[sheet.vertex].vertexes[i] = -1;
                    break;
                }     
            }
            
            adjacencyList.erase(sheet.vertexNumber);
        }  
    }

    bool isSheet(int quantity)
    {
        return quantity == 1;
    }

    bool isUsed(int quantity)
    {
        return quantity == 0;
    }

    void initQueue()
    {
        for (size_t i = 1; i <= quantityOfVertex; i++)
        {
            Queue.push(i);
        }
    }
};