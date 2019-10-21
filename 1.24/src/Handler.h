#include <iostream>
#include <set>
#include <cstdlib> 
#include <cctype>
#include "FileRead.h"
#include "State.h"
#include "Syntax.h"
#include "Operators.h"
#include "../config/keyWords.h"

#define FILE_NAME "test.txt"
#define ERROR -99999
#define LINE_COMENTS_OPERATOR "//"
#define SUCSSES_MESSAGE "allright"
#define ERROR_MESSAGE "Syntax error"

using namespace std;

class Handler
{
private:

void initSets(set<string> &openOperators, set<string> &closeOperators)
{
    openOperators.insert(REPEAT_KEY_WORD);
    openOperators.insert(BEGIN_KEY_WORD);
    openOperators.insert(RECORD_KEY_WORD);
    openOperators.insert(CASE_KEY_WORD);
    closeOperators.insert(END_KEY_WORD);
    closeOperators.insert(UNTIL_KEY_WORD);
}

void nestingHandler(set<string> openOperators,  set<string> closeOperators, int &nestingListener, string word)
{
    if(openOperators.find(word) != openOperators.end())
    {
        nestingListener++;
    }
    if(closeOperators.find(word) != closeOperators.end())
    {
        nestingListener--;
    }
}

void readWordHandler(FILE *f, set<string> openOperators,  set<string> closeOperators, int &pastOperatorCode, int &nestingListener)
{
    FileRead fileRead;
    Operators operators;
    Syntax syntax;
    string word;
    bool isCorrect;
    if (fileRead.word(f, word))
    {
        if((openOperators.find(word) != openOperators.end()) || (closeOperators.find(word) != closeOperators.end()) || word == "const" || word == "type")
        {
            nestingHandler(openOperators, closeOperators, nestingListener, word);
            int operatorCode = operators.getCode(word);
            isCorrect = syntax.chek(pastOperatorCode, operatorCode);
            pastOperatorCode = operatorCode;
            if (!isCorrect)
            {
                cout << ERROR_MESSAGE << endl;
                throw exception();
            }
            
        }
    }
}

void readSymbolHandler(FILE * f)
{
    FileRead fileRead;
    fileRead.symbol(f);
}

public:

void start(FILE * f)
{
    int nestingListener = 0;
    set<string> openOperators;
    set<string> closeOperators;
    initSets(openOperators, closeOperators);
    
    State state;
    int pastOperator = NO_OPERATOR;
    while (!feof(f))
    { 
        int readState = state.next(f);
        switch (readState)
        {
            case READY_FOR_SYMBOL:
                readSymbolHandler(f);
                break;
            case READY_FOR_WORD:
                readWordHandler(f, openOperators, closeOperators, pastOperator, nestingListener);
                break;
            default:
                break;
        }
        if (nestingListener < 0)
        {
            cout << ERROR_MESSAGE;
            throw exception();
        } 	     	    
    }
    if(nestingListener != 0)
    {
        cout << ERROR_MESSAGE << endl;
        throw exception();
    }            
}
};