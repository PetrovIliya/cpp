#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <sstream>

#define CITY_FILE_NAME "cities.txt"
#define ROAD_FILE_NAME "roads.txt"
#define MAX_VALUE 99999999;

using namespace std;

struct Mark
{
    int mark;
    bool isSolid;
    int distance;
};

struct Road
{
    int from;
    int to;
    int length;
};

class Matrix
{
public:

    Matrix()
    {
        citiesFile.open(CITY_FILE_NAME);
        roadsFile.open(ROAD_FILE_NAME);
        checkFiles();
        initMatrixSize();
        initMatrix();
        printMatrix();
        citiesFile.close();
        roadsFile.close();
    }

    map <int, map <int, int>> getMatrix()
    {
        return matrix;
    }

    int getMatrixSize()
    {
        return matrixSize;
    }

private:
    int matrixSize = 0;
    map <int, map <int, int>> matrix;
    ifstream citiesFile;
    ifstream roadsFile;

    void checkFiles()
    {
        if (roadsFile.peek() == ifstream::traits_type::eof())
        {
            cout << "road file is empty";
            throw exception();
        } 
        if (citiesFile.peek() == ifstream::traits_type::eof())
        {
            cout << "city file is empty";
            throw exception();
        } 
    }

    void initMatrix()
    {
        string roadInfo;
        Road road;
        for(int j = 0; j < matrixSize; j++)
        {
            for(int i = 0; i < matrixSize; i++)
            {
                matrix[i][j] = MAX_VALUE;
            }
        }

        while (getline(roadsFile, roadInfo)) 
        {
            road = getRoad(roadInfo);

            matrix[road.from - 1][road.to - 1] = road.length;
            matrix[road.to - 1][road.from - 1] = road.length;
        }
    }

    void printMatrix()
    {
        int maxLength = 8;
        for(int j = 0; j < matrixSize; j++)
        {
            for(int i = 0; i < matrixSize; i++)
            {
                int length = to_string(matrix[i][j]).length();
                int currLength = maxLength - length;
                printSpacesByLength(currLength / 2);
                cout << matrix[i][j];
                printSpacesByLength(currLength / 2 + 5);
            }
            cout << endl;
        }
    }

    void printSpacesByLength(int length)
    {
        for (size_t n = 0; n < length; n++)
        {
            cout << " ";
        }
    }

    void initMatrixSize()
    {
        bool isFirst = true;
        string cityInfo;
        while (getline(citiesFile, cityInfo)) 
        {
            matrixSize++;
        }
    }

    Road getRoad(string roadInfo)
    {
        Road road;
        std::istringstream in(roadInfo);
        string from, to, length, isDangerius;
        in >> from >> to >> length >> isDangerius;
    
        road.from = stoi(from);
        road.to = stoi(to);
        road.length = stoi(length);
        if (isDangerius == "y") 
        {
            road.length *= 100;
        }

        return road;
    }

    int charToInt(char ch)
    {
        return ch - '0';
    }

};