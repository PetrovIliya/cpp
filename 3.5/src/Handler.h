#include "Matrix.h"
#include <iterator>

class Handler
{
public:

    Handler()
    {
        matrix = matrixObj.getMatrix();
        matrixSize = matrixObj.getMatrixSize();
    }

    void searchWay()
    {
        Mark marks[matrixSize];
        vector <int> userInput = getUserInput(matrixSize);

        for (int i = 0; i < matrixSize; i++) 
        {
            marks[i].isSolid = false;
            marks[i].distance = MAX_VALUE;
            marks[i].mark = 0;
        }
        int lastSolid = userInput[0];
        marks[lastSolid].mark = 0;
        marks[lastSolid].isSolid = true;
        marks[lastSolid].distance = 0;

        marks[matrixSize] = getMarks(lastSolid, marks, userInput[0], userInput[1]);

       printMarks(marks, userInput[0], userInput[1]);
    }

private:
    Matrix matrixObj;
    int matrixSize;
    map <int, map <int, int>> matrix;

    void printMarks(Mark marks[], int start, int end)
    {
        int curr = end;
        map <int, int> vertexes;

        cout << "shortest way from " << start + 1 << " to " << end + 1 << ": " << endl;

        while (curr != start) 
        {
            vertexes[vertexes.size() + 1] = marks[curr].mark + 1;  
            curr = marks[curr].mark;
        }
        auto rev = vertexes.rbegin();
        for(size_t i=0; i < vertexes.size(); ++i, ++rev)
        {
            cout << vertexes[rev->first] << " ";
        }
        cout << end + 1;
    }

   
    Mark getMarks(int lastSolid, Mark marks[], int start, int end)
    {
        int newLastSolid = 0;
        int smallestValue = MAX_VALUE;
        bool isAllSolid = true;

        for (int i = 0; i < matrixSize; i++) 
        {
            if (!marks[i].isSolid && marks[lastSolid].distance + matrix[lastSolid][i] < marks[i].distance) 
            {
                marks[i].distance = marks[lastSolid].distance + matrix[lastSolid][i];
                marks[i].mark = lastSolid;
            }
        }
        for (int i = 0; i < matrixSize; i++) 
        {
            if (!marks[i].isSolid && marks[i].distance < smallestValue) 
            {
                smallestValue = marks[i].distance;
                newLastSolid = i;
            }
        }
        marks[newLastSolid].isSolid = true;
        for (int i = 0; i < matrixSize; i++) 
        {
            if (!marks[i].isSolid) 
            {
                isAllSolid = false;
            }
        }
        if (lastSolid == newLastSolid) 
        {
            if (!isAllSolid) 
            {
                cout << "ways from vertex: " << ++start << " to vertex " << ++end << " does not exist." << endl;
                exit(0);
            }
        } 
        else if (!marks[end].isSolid)
        {
           marks[matrixSize] = getMarks(newLastSolid, marks, start, end);
        }

        return marks[matrixSize];
    }

    vector <int> getUserInput(int matrixSize)
    {
        int startVertex;
        int endVertex;
        while (true)
        {
            cout << endl << "enter number of start vertex: ";
            cin >> startVertex;
            if (isCorrectInput(startVertex, matrixSize))
                break;
        }
        while (true)
        {
            cout << endl << "enter number of end vertex: ";
            cin >> endVertex;
            if (isCorrectInput(endVertex, matrixSize))
                break;
        }

        return {startVertex - 1, endVertex - 1};        
    }

    bool isCorrectInput(int input, int matrixSize)
    {
        if(cin.good()) 
        {
            if (input >= matrixSize + 1 || input < 0) 
            {
                cout << "number of vertex should be less then quantity of cities but more then 0" << endl << "try again:";
                return false;
            }
        } 
        else 
        {
            cout << endl << "entered data is not a number" << endl;
            throw exception();
        }

        return true;
    }
};