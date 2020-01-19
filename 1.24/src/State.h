#include <fstream>
#include <string.h>
#include "../config/states.h"

using namespace std;

class State
{
    public: 
int next(FILE *&f, int &lineCounter)
{
    string specialSymbol;
    int state = NO_STATE;
    char ch = fgetc(f);
    if(feof(f))
    {
        state = EOF_STATE;
    }
    else if(ch == '\n')
    {
        state = EOLN_STATE;
        lineCounter++;
    }
    else if (ch == ' ')
    {
        state = NO_STATE;
    }
    else if (!isLetter(ch))
    {
        state = READY_FOR_SYMBOL;
        fseek(f, -1, SEEK_CUR);
    }
    else if(isLetter(ch))
    {
        state = READY_FOR_WORD;
        fseek(f, -1, SEEK_CUR);
    }
    return state;
}

private :

bool isLetter(char ch)
{
    if(ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z')
    {
    return true;
    }
    else
    {
        return false;
    }
}

};