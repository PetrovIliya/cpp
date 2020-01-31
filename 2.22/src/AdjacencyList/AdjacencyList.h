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

    void setQuantityOfVertex(fstream &file)
    {
        string readString;
        getline(file, readString);
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
        string readString;
        while (getline(file, readString))
        {
            std::istringstream in(readString);
            int a, b;
            in >> a >> b;
            adjacencyList[a].vertexes[adjacencyList[a].vertexes.size()] = b;
            adjacencyList[b].vertexes[adjacencyList[b].vertexes.size()] = a;
        }
    }
};

