#include "stdafx.h"
#include "CTask.h"

int main()
{
	try
	{
		std::ifstream fileIn("input2.txt");
		if (!fileIn.is_open())
		{
			throw  std::exception("File input.txt has not opened for reading.");
		}
		std::ofstream fileOut("output.txt");
		if (!fileOut.is_open())
		{
			throw  std::exception("File output.txt has not opened for reading.");
		}
		CTask task(fileIn, std::cout);
		task.GetSolution();
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << "\n";
	}
	return 0;
}

