/*
2.1. Квадратное озеро (6)
Квадратное озеро с островами задается матрицей размером N x N (1 < N < 300). Каждый
элемент матрицы содержит либо символ @; (собака), обозначающий территорию, которая
включает часть острова, либо символ .; (точка), обозначающий участок свободной воды. В левом
верхнем углу озера находится квадратный плот размером M x M (1 < M < N) клеток.
За один шаг плот может сдвигаться на одну клетку по горизонтали или вертикали. Плот и
остров не могут иметь общих клеток. Требуется определить минимальное число шагов,
необходимых для того, чтобы плот достиг правого нижнего угла озера.
Ввод из файла INPUT.TXT. В первой строке содержатся числа N и M, разделенные пробелами.
В следующих N строках находится матрица, представляющая озеро, по N подряд идущих
символов в строке. Подматрица размером M x M, находящаяся в левом верхнем углу, не содержит
островов, то есть начальное положение плота всегда допустимо.
Вывод: файл OUTPUT.TXT должен содержать единственное число — количество
необходимых шагов. Если правого нижнего угла достичь невозможно, то в файл выводится No.

Выполнил: Матюков Николай Юрьевич ПС-21

*/
#include "stdafx.h"
#include <iostream>
#include <queue>
#include <fstream>
#include <string> 
#include <vector>
using namespace std;
using LakeVec = vector<vector<int>>;

const int BORDER = -3;
const int ISLAND = -1;
const int PROHIBITED_ZONE = -2;
const int WATER = 0;

struct Cell
{
	int x;
	int y;
	int level;
	bool isVisited;
};

void PrintMatrix(LakeVec &lakeMatrix)
{
	for (int i = 0; i < lakeMatrix.size(); ++i)
	{
		for (int j = 0; j < lakeMatrix.size(); ++j)
		{
			if (lakeMatrix[i][j] == -3 || lakeMatrix[i][j] == -2 || lakeMatrix[i][j] == -1)
				cout << lakeMatrix[i][j];
			else
				cout << " " << lakeMatrix[i][j];
		}
		cout << endl;
	}
}

void CreateMatrixLake(ifstream &fIn, LakeVec &lakeMatrix, queue <Cell> &islandCoords)
{
	Cell coordsIsland;
	for (int i = 0; i < lakeMatrix.size(); ++i)
		for (int j = 0; j < lakeMatrix.size(); ++j)
		{
			if (((i == 0) || (i == lakeMatrix.size() - 1))
				|| ((j == 0) || (j == lakeMatrix.size() - 1)))
			{
				lakeMatrix[i][j] = BORDER;
			}
			else {
				char ch;
				fIn >> ch;
				if (ch == '.')
				    lakeMatrix[i][j] = WATER;
				if (ch == '@')
					lakeMatrix[i][j] = ISLAND;
			}
			if (lakeMatrix[i][j] == ISLAND)
			{
				coordsIsland.x = i;
				coordsIsland.y = j;
				islandCoords.push(coordsIsland);
			}
		}
}

void PaintTerritoryAroundIsland(LakeVec &lakeMatrix, int lakeSz, int raftSz, queue <Cell> &islandCoords)
{
	while (!(islandCoords.empty()))
	{
		Cell coordsIsland;
		coordsIsland = islandCoords.front();
		islandCoords.pop();
		for (int i = coordsIsland.x; (i != coordsIsland.x - raftSz) & (i != 0); i--)
		{
			for (int j = coordsIsland.y; (j != coordsIsland.y - raftSz) & (j != 0); j--)
			{
				if (lakeMatrix[i][j] == BORDER)
					break;
				if (lakeMatrix[i][j] == ISLAND)
					continue;
				lakeMatrix[i][j] = PROHIBITED_ZONE;
			}
		}
	}
}

void VisitCell(LakeVec &lake, queue <Cell> &q, Cell currPos, const int dX, const int dY)
{
	if (lake[currPos.x + dX][currPos.y + dY] == 0)
	{
		int level;
		level = currPos.level;
		level++;
		lake[currPos.x + dX][currPos.y + dY] = level;
		currPos.x += dX;
		currPos.y += dY;
		currPos.level = level;
		q.push(currPos);
	}
}

void SearchOfAWay(LakeVec &lake)
{
	queue <Cell> q;
	Cell currCell;
	currCell.x = 1;
	currCell.y = 1;
	currCell.level = 1;
	lake[currCell.x][currCell.y] = currCell.level;
	q.push(currCell);
	while (q.size() > 0)
	{
		Cell currPos = q.front();
		q.pop();
		VisitCell(lake, q, currPos, 1, 0);
		VisitCell(lake, q, currPos, -1, 0);
		VisitCell(lake, q, currPos, 0, 1);
		VisitCell(lake, q, currPos, 0, -1);
	}
}

bool CheckCrossingInStartPos(LakeVec &lakeMatrix, int raftSize)
{
	for (int i = 1; i < raftSize; ++i)
		for (int j = 1; j < raftSize; ++j)
		{
			if (lakeMatrix[i][j] == ISLAND)
			{
				return false;
			}
		}
	return true;
}

int main(int argc, char* argv[])
{
	ifstream fileIn("input.txt");
	if (!fileIn.is_open())
	{
		cout << "File " << argv[1] << " has not opened for reading.";
		return 1;
	}
	ofstream fileOut("output.txt");
	if (!fileOut.is_open())
	{
		cout << "File " << argv[2] << " has not opened for writing.";
		return 1;
	}
	int lakeSize;
	int raftSize;
	fileIn >> lakeSize;
	fileIn >> raftSize;
	if ((raftSize >= lakeSize) || (lakeSize > 300))
	{
		cout << "Error: incorrect entrance data." << endl;
		return 1;
	}
	lakeSize += 2;
	LakeVec lake(lakeSize, vector<int>(lakeSize, 0));
	queue <Cell> islandCoords;
	CreateMatrixLake(fileIn, lake, islandCoords);
	//PrintMatrix(lake);
	if (!CheckCrossingInStartPos(lake, raftSize))
	{
		cout << "Error: incorrect entrance data. On start a raft collision with the island." << endl;
		return 1;
	}
	PaintTerritoryAroundIsland(lake, lakeSize, raftSize, islandCoords);
	//PrintMatrix(lake);
	SearchOfAWay(lake);
	//PrintMatrix(lake);
	int pos = (lake.size() - 1) - raftSize;
	if (lake[pos][pos] != 0)
	{
		fileOut << lake[pos][pos] - 1 << endl;
	}
	else
	{
		fileOut << "No" << endl;
	}
    return 0;
}
