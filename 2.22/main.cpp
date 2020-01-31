#include "src/Handler/Handler.h"

using namespace std;

#define FILE_NAME "INPUT.txt"

int main()
{  
    Handler handler(FILE_NAME);
    cout << handler.getShortestWay();
    return 0;
}