/* Автор: Илья Петров
   Программа  на ПАСКАЛЕ включает такие сочетания ключевых
   слов, как  REPEAT..UNTIL, RECORD..END, CASE..END и BEGIN..END.
   Некоторые части программы могут быть  закомментированы, другие
   части текста могут представлять собой  константы в апострофах.
   Требуется проверить правильность вложенности этих  конструкций
   с учетом допустимости взаимных вложений
   */

#include "src/Handler.h"

int main() 
{ 
    Handler handler;
    FILE * f = fopen(FILE_NAME, "r");
    try
    {
        handler.start(f);
        fclose(f);   
    }
    catch(const exception& e)
    {
        return EXIT_FAILURE;
    }
    
    cout << SUCSSES_MESSAGE << endl;
}
