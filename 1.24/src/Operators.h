#include "../config/operatorCodes.h"
#include <iostream>

using namespace std;

class Operators
{

public:

    int getCode(string keyWord)
    {
        if (keyWord == "begin")
        {
            return BEGIN;
        }
        if (keyWord == "end")
        {
            return END;
        }
        if (keyWord == "repeat")
        {
            return REPEAT;
        }
        if (keyWord == "until")
        {
            return UNTIL;
        }
        if (keyWord == "record")
        {
            return RECORD;
        }
        if (keyWord == "case")
        {
            return CASE;
        }
        if (keyWord == "const")
        {
            return CONST;
        }
        if (keyWord == "of")
        {
            return OF;
        }
        if (keyWord == "type")
        {
            return TYPE;
        }
        else
        {
            return -1;
        }    
    }
};