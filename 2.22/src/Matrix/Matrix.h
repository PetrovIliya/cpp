#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <map>

#define NOT_FILLED 0
#define FILLED 1

using namespace std;

struct MatrixElement
{
    int flag = NOT_FILLED;
    bool used = false;
};

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

    map<int, map<int, MatrixElement>> getMatrix()
    {
        return matrix;
    }

private:
    map<int, map<int, MatrixElement>> matrix;
    int quantityOfComputers;
    vector<vector<int>> computerConnections;

    void initMatrix()
    {
        for (vector<int> computerConnection : computerConnections)
        {
            matrix[computerConnection[0]][computerConnection[1]].flag = FILLED;
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
                MatrixElement matrixElement;
                matrix[i][j] = matrixElement;
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

