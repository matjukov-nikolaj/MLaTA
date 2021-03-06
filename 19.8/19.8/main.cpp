// 19.8.cpp :
/*19.8.Сапер(3)

	В некоторых клетках прямоугольной таблицы M×N(0 & lt; M, N ≤ 10) имеются “мины”(игра
	Minesweeper).Проставить во всех клетках таблицы либо символ мины ‘*’, либо число от 0 до 8,
	показывающее число мин в соседних клетках по горизонтали, вертикали или диагонали.
	Ввод.Первая строка файла INPUT.TXT содержит целые числа M и N через пробел, задающие
	число строк и столбцов соответственно.Каждая из последующих M строк содержит ровно N
	символов.Безопасные клетки обозначаются ‘ + ’, а мины ‘*’.
	Вывод.В файл OUTPUT.TXT вывести M строк по N символов.

	Пример
	Ввод
	3 5
	++*+*
	**++ +
	+*+**
	Вывод
	23 * 2 *
	**443
	3 * 3 * *
	
	Матюков Николай Юрьевич

*/
//

#include "stdafx.h"
#include "CSapper.h"


int main()
{
	try
	{
		std::ifstream fileIn("input.txt");
		if (!fileIn.is_open())
		{
			throw  std::exception("File input.txt has not opened for reading.");
		}
		std::ofstream fileOut("output.txt");
		if (!fileOut.is_open())
		{
			throw  std::exception("File output.txt has not opened for reading.");
		}
		CSapper saper(fileIn, fileOut);
		saper.PrintField();
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << "\n";
	}
	return 0;
}

