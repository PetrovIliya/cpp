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
#define ERROR_MESSAGE "Syntax error at line: "

using namespace std;

class Handler
{

public:
int lineCounter = 1;
int nestingListener = 0;
set<string> openOperators;
set<string> closeOperators;
FileRead fileRead;

void start(FILE * f)
{
    initSets();
    State state;
    int pastOperator = NO_OPERATOR;
    while (!feof(f))
    { 
        int readState = state.next(f, lineCounter);
        switch (readState)
        {
            case READY_FOR_SYMBOL:
                fileRead.symbol(f, lineCounter);
                break;
            case READY_FOR_WORD:
                readWordHandler(f, pastOperator);
                break;
            default:
                break;
        }
        if (nestingListener < 0)
        {
            cout << ERROR_MESSAGE + to_string(lineCounter) + " (nesting)";
            throw exception();
        } 	     	    
    }
    if(nestingListener != 0)
    {
        cout << ERROR_MESSAGE + to_string(lineCounter) + " (nesting)" << endl;
        throw exception();
    }            
}

private:

void initSets()
{
    openOperators.insert(REPEAT_KEY_WORD);
    openOperators.insert(BEGIN_KEY_WORD);
    openOperators.insert(RECORD_KEY_WORD);
    openOperators.insert(CASE_KEY_WORD);
    closeOperators.insert(END_KEY_WORD);
    closeOperators.insert(UNTIL_KEY_WORD);
}

void nestingHandler(string word)
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

void readWordHandler(FILE *f, int &pastOperatorCode)
{
    FileRead fileRead;
    Operators operators;
    Syntax syntax;
    string word;
    bool isCorrect;
    if (fileRead.word(f, word, lineCounter))
    {
        if((openOperators.find(word) != openOperators.end()) || (closeOperators.find(word) != closeOperators.end()) || word == "const" || word == "type" || word == "of")
        {
            nestingHandler(word);
            int operatorCode = operators.getCode(word);
            isCorrect = syntax.chek(pastOperatorCode, operatorCode);
            pastOperatorCode = operatorCode;
            if (!isCorrect)
            {
                cout << ERROR_MESSAGE + to_string(lineCounter) + " (syntax)";
                throw exception();
            }
            
        }
    }
}
};