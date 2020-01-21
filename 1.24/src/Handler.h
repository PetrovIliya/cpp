#include <iostream>
#include <set>
#include <cstdlib> 
#include <cctype>
#include "FileRead.h"
#include "State.h"
#include "Syntax.h"
#include "Operators.h"
#include "../config/keyWords.h"
#include <stack>

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
    stack <int> stack;
    Operators operators;
    int pastOperator = NO_OPERATOR;
    Syntax syntax;
    int operatorCode;

    void start(FILE * f)
    {
        initSets();
        State state;
        while (!feof(f))
        { 
            int readState = state.next(f, lineCounter);
            switch (readState)
            {
                case READY_FOR_SYMBOL:
                    fileRead.symbol(f, lineCounter);
                    break;
                case READY_FOR_WORD:
                    readWordHandler(f);
                    break;
                default:
                    break;
            }	     	    
        }
        if(!stack.empty())
        {
            throwNestingErrorMessage();
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

    void emptyStackHandler(string word)
    {
        if(closeOperators.find(word) != closeOperators.end())
        {
            throwNestingErrorMessage();
        }
        operatorCode = operators.getCode(word);
    }

    void notEmptyStackHandler(string word)
    {
        if (word == "record")
        {
            throwNestingErrorMessage();
        }
        operatorCode = operators.getCode(word);
        bool isCorrect = syntax.chek(stack.top(), operatorCode);
    }

    void nestingHandler(string word)
    {
        if (stack.empty())
        {
            emptyStackHandler(word);
        }
        else
        {
           notEmptyStackHandler(word);
        }    
        if(openOperators.find(word) != openOperators.end())
        {
            stack.push(operatorCode);
        }
        if(closeOperators.find(word) != closeOperators.end())
        {
            stack.pop();
        }
    }

    void readWordHandler(FILE *f)
    {
        FileRead fileRead;
        string word;
        if (fileRead.word(f, word, lineCounter))
        {
            if(needToCheck(word))
            {
                nestingHandler(word);   
            }
        }
    }

    void throwSyntaxErrorMessage()
    {
        cout << ERROR_MESSAGE + to_string(lineCounter) + " (syntax)";
        throw exception();
    }

    void throwNestingErrorMessage()
    {
        cout << ERROR_MESSAGE + to_string(lineCounter) + " (nesting)" << endl;
        throw exception();
    }

    bool needToCheck(string word)
    {
        return (openOperators.find(word) != openOperators.end()) || (closeOperators.find(word) != closeOperators.end()) || word == "const" || word == "type" || word == "of";
    }

};