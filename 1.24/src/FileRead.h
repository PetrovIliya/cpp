//Методы класса читают либо слово, либо символ, пропускают коментарии и обрабатывют апострафы
#include <fstream>
#include <string.h>
#include "../config/states.h"
#include <exception>

using namespace std;

class FileRead
{

public:

void symbol(FILE *&f)
{
    char specialSymbol = fgetc(f);
    if (specialSymbol == '/')
    {
        if (!feof(f))
        {
            if (specialSymbol == '/')
            {
                skipLine(f);
            }
        }       
    }
    if(specialSymbol == '{')
    {
        skipComentedBlock(f);
    }
    if(specialSymbol == '\'')
    {
        apostropheHandler(f);
    }
    
}

bool word(FILE * &f, string &word)
{
    char symbol = '\n';
    if (!feof(f))
    {
    symbol = fgetc(f);
    buildWord(f, word, symbol);
    }    
    while (!feof(f) && symbol != ' ' && symbol != '\n' && isLetter(symbol))
    {
        symbol = fgetc(f);
        buildWord(f, word, symbol);
    }  
    if (!feof(f) && !isLetter(symbol) && symbol != ' ' && symbol != '\n')
    {
        fseek(f, -1, SEEK_CUR);
    } 
    if(word.length() == 0)
    {
        return false;
    }
    else
    {
        return true;
    }                     
}

private :

void apostropheHandler(FILE *&f)
{
    while(!feof(f))
    {
        char symbol = fgetc(f);
        if (symbol == '\'')
        {
            return;
        }
        if (symbol == '\\')
        {
            if (!feof(f))
            {
                symbol = fgetc(f);
            }
        }
    }
    cout << "Syntax error";
    throw exception();   
}

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

void buildWord(FILE *f, string &word, char symbol)
{
    if(!feof(f) && symbol != ' ' && symbol != '\n' && isLetter(symbol))
    {
        symbol = tolower(symbol);
        word += symbol;
    }  
}

void skipComentedBlock(FILE * &f)
{
    while(!feof(f))
    {
        char symbol = fgetc(f);
        if(symbol == '}')
        {
            break;
        }
    }
}

void skipLine(FILE * &f)
{
    char ch;
    if (!feof(f))
    {
    ch = fgetc(f);
    } 
    while (ch != '\n' && !feof(f))
    {
        ch = fgetc(f);
    }
}

};