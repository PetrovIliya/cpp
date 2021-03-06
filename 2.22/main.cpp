/* 
Петров Илья
В офисе  фирмы  Megasoft  установлены  N  компьютеров  с 
номерами от 1 до N, некоторые из них  соединены  между  собой. 
Сообщение между соединенными компьютерами проходит в любом  из 
двух направлений за 1 с. Компьютер,  получив  сообщение, сразу 
отправляет  его  всем  соединенным  с  ним  компьютерам.  Cеть 
устроена так, что между любыми двумя компьютерами  есть  путь, 
причем только один. Найти номера всех компьютеров,  с  которых 
главный программист Гилл Бейтс может отправить сообщение  так, 
чтобы максимальная задержка в  получении  сообщения  была  как 
можно меньше. 
  Ввод из файла INPUT.TXT. В первой строке вводится значение N 
(1<=N<=10^5). В каждой из следующих N-1  строк  вводится через 
пробел пара номеров компьютеров, обозначающая соединение.
  Вывод в файл OUTPUT.TXT. В первой строке выводится количество
искомых компьютеров M. Во второй строке выдаются через пробел в
порядке возрастания номера искомых компьютеров.
  Пример
  Ввод
4
1 2
4 3
2 3
  Вывод
2
2 3
  Указание. Предложить структуру данных, обеспечивающую быстрое
нахождение листьев бескорневого дерева из условия задачи (15). */

#include "src/Handler/Handler.h"

using namespace std;

#define FILE_NAME "INPUT.txt"
#define OUTPUT_FILE_NAME "OUTPUT.TXT"



int main()
{  
    try
    {
        Handler handler(FILE_NAME);
        vector<int> computers =  handler.getShortestWay();
        remove(OUTPUT_FILE_NAME);
        ofstream file(OUTPUT_FILE_NAME);
        
        file << computers.size() << '\n';
        for (int computer: computers)
        {
            file << computer << ' ';
        }
        file.close();
        cout << "Done";
    }
    catch(const exception& e)
    {
        return EXIT_FAILURE;
    }
    
    return 0;
}