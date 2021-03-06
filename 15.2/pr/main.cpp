//15.2.Игра в умножение(6)
//Двое играют в умножение : умножают целое число P на одно из чисел от 2 до 5. Первый игрок
//всегда начинает с P = 1, делает умножение, затем число умножает второй игрок, снова первый и т.
//д.Перед началом игры им задают число N, и победителем считается тот, кто первым добьется
//условия P ≥ N.Определить, кто выиграет при заданном N, если оба играют наилучшим образом.
//Ограничения : 2  N 10000, время 1 с.
//	Ввод из файла INPUT.TXT.В первой строке находится количество партий M.В следующих M
//	строках задаются значения N для каждой партии.
//	Вывод в файл OUTPUT.TXT.Выводится М строк с числами 1 – если победит первый игрок,
//	или 2 - если победит второй.
//	Пример
//	Ввод
//	1
//	17
//	Вывод
//	1


// Матюков Николай Юрьевич ПС-21

#include "stdafx.h"
#include "CMultiplicationGame.h"

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
		CMultiplicationGame game(fileIn, fileOut);
		game.PrintWinnersLIst();
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << "\n";
	}
	return 0;
}
