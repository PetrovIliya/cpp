#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <map>

#define EMPTY 0
#define FILLED 1

using namespace std;

class Matrix
{
public:

    Matrix(fstream &file)
    {
        setQuantityOfComputers(file);
        setComputerConnections(file);
        fillMatrixByElements();
        initMatrix();
    } 

    int getQuantityOfComputers()
    {
        return quantityOfComputers;
    } 

    map<int, map<int, int>> getMatrix()
    {
        return matrix;
    }

private:
    map<int, map<int, int>> matrix;
    int quantityOfComputers;
    vector<vector<int>> computerConnections;

    void initMatrix()
    {
        for (vector<int> computerConnection : computerConnections)
        {
            matrix[computerConnection[0]][computerConnection[1]] = FILLED;
        }
    }

    void setQuantityOfComputers(fstream &file)
    {
        string readString;
        getline(file, readString);
        quantityOfComputers = stoi(readString);
    }

    void fillMatrixByElements()
    {
        for (int i = 1; i <= quantityOfComputers; i++)
        {
            for (int j = 1; j <= quantityOfComputers; j++)
            {
                matrix[i][j] = EMPTY;
            }
        }  
    }

    void setComputerConnections(fstream &file)
    {
        string readString;
        vector<vector<int>> computerConnections;
        while (getline(file, readString))
        {
            std::istringstream in(readString);
            int a, b;
            in >> a >> b;
            vector<int> temp;
            temp.push_back(a);
            temp.push_back(b);
            computerConnections.push_back(temp);
        }
        
        Matrix::computerConnections = computerConnections;
    }
};

