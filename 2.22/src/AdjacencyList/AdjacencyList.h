#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <map>

using namespace std;

struct VertexData
{
    map <int, int> vertexes;
    int quantity = 0;
};

class AdjacencyList
{
public:
    AdjacencyList(fstream &file)
    {
        setQuantityOfVertex(file);
        setAdjacencyList(file);
        setQuantityForEachVortex();
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

private:
    int quantityOfVertex;
    map<int, VertexData> adjacencyList;

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

    void setQuantityForEachVortex()
    {
        for (size_t i = 1; i <= quantityOfVertex; i++)
        {
            adjacencyList[i].quantity = adjacencyList[i].vertexes.size();
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
            checkForDigit(from);
            checkForDigit(to);
            int fromInt, toInt;
            fromInt = stoi(from);
            toInt = stoi(to);
        
            adjacencyList[fromInt].vertexes[adjacencyList[fromInt].vertexes.size()] = toInt;
            adjacencyList[toInt].vertexes[adjacencyList[toInt].vertexes.size()] = fromInt;
        }

        if (quantiyOfLines != quantityOfVertex - 1)
        {
            cout << "warning: invalid quantity of parameters";
            throw exception();
        }   
    }
};

