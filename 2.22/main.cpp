#include <iostream>
#include <cstdlib> 
#include <cctype>
#include <stack>
#include <queue> 
#include "src/Matrix/Matrix.h"

#define FILE_NAME "INPUT.txt"

using namespace std;

struct computer
{
    int position, prtvPosition;
    bool used;
};

int main()
{
    fstream file(FILE_NAME);
    vector<bool> used;
    queue<int> queue;
    int quantityOfComputers, startPosition;
    vector<int> prevComputers;
    Matrix matrix(file);
    map<int, map<int, MatrixElement>> graf = matrix.getMatrix();
    cout << graf[1][2].flag;
    return 0;
}

