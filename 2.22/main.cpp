#include "src/Handler/Handler.h"

using namespace std;

#define FILE_NAME "INPUT.txt"

int main()
{  
    Handler handler(FILE_NAME);
    vector<Sheet> test =  handler.getShortestWay();
    for (Sheet sheet : test)
    {
        cout << sheet.vertex;
    }
    
    return 0;
}