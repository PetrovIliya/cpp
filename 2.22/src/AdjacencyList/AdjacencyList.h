#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <map>

using namespace std;

struct VertexData
{
    map <int, int> vertexes;
    map <int, int> vertexesPtrs;
    int quantity = 0;
    int length = 0;
};

class AdjacencyList
{
public:
    AdjacencyList(fstream &file)
    {
        setQuantityOfVertex(file);
        if (quantityOfVertex < 1)
        {
            cout << "wrong quantity of vertexes";
            throw exception();
        }      
        
        setAdjacencyList(file);
        setQuantityForEachVortexAndQueue();
    }

    AdjacencyList()
    {}

      map<int,VertexData> getAdjacencyList()
      {
          return adjacencyList;
      }

      int getQuantityOfVertex()
      {
          return quantityOfVertex;
      }

       queue<int> getQueueOfSheets()
       {
           return queueOfSheets;
       }

private:
    int quantityOfVertex;
    map<int, VertexData> adjacencyList;
    queue<int> queueOfSheets;

    void checkForDigit(string arg)
    {
        for (char s : arg)
        {
            if (!isdigit(s))
            {
                cout << "entered data is not a digit";
                throw exception();
            }
        }
    }

    void setQuantityOfVertex(fstream &file)
    {
        string readString;
        getline(file, readString);
        checkForDigit(readString);
        
        quantityOfVertex = stoi(readString);
    }

    void setQuantityForEachVortexAndQueue()
    {
        if (quantityOfVertex == 1)
        {
            queueOfSheets.push(1);
            return;
        }
        
        for (size_t i = 1; i <= quantityOfVertex; i++)
        {  
            int quantity = adjacencyList[i].vertexes.size();
            adjacencyList[i].quantity = quantity;
            if (quantity == 1) //Лист найден
            {
                queueOfSheets.push(i);
            }
            
        }
    }

    void setAdjacencyList(fstream &file)
    {
        int quantiyOfLines = 0;
        string readString;
        while (getline(file, readString))
        {
            quantiyOfLines++;
            std::istringstream in(readString);
            string from, to;
            in >> from >> to;
            // checkForDigit(from); Для более высококой производительности убрал проверку
            // checkForDigit(to);
            int fromInt, toInt;
            fromInt = stoi(from);
            toInt = stoi(to);

            int fromMapSize = adjacencyList[fromInt].vertexes.size();
            int toMapSize = adjacencyList[toInt].vertexes.size();
        
            adjacencyList[fromInt].vertexes[fromMapSize] = toInt;
            adjacencyList[fromInt].vertexesPtrs[toInt] = fromMapSize;
            adjacencyList[toInt].vertexes[toMapSize] = fromInt;
            adjacencyList[toInt].vertexesPtrs[fromInt] = toMapSize;
        }

        if (quantiyOfLines != quantityOfVertex - 1)
        {
            cout << "warning: invalid quantity of parameters";
            throw exception();
        }   
    }
};

