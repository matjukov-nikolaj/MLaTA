#include "stdafx.h"
#include <iostream>
#include <queue>
#include <fstream>
#include <string> 
using namespace std;

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

void CreateMatrixLake(ifstream &fIn, int **lakeMatrix, int lakeSz, queue <Cell> &islandCoords)
{
	Cell coordsIsland;
	for (int i = 1; i <= lakeSz; ++i)
		for (int j = 1; j <= lakeSz; ++j)
		{
			if (((i == 1) || (i == lakeSz))
				|| ((j == 1) || (j == lakeSz)))
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

void PaintTerritoryAroundIsland(int **lakeMatrix, int lakeSz, int raftSz, queue <Cell> &islandCoords)
{
	while (!(islandCoords.empty()))
	{
		Cell coordsIsland;
		coordsIsland = islandCoords.front();
		islandCoords.pop();
		for (int i = coordsIsland.x; (i != coordsIsland.x - raftSz) & (i != 1); i--)
			for (int j = coordsIsland.y; (j != coordsIsland.y - raftSz) & (j != 1); j--)
			{
				if ((lakeMatrix[i][j] == BORDER) || (lakeMatrix[i][j] == ISLAND))
					continue;
				lakeMatrix[i][j] = PROHIBITED_ZONE;
			}
	}
}

void VisitCell(int **lake, queue <Cell> &q, Cell currPos, const int dX, const int dY)
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

void SearchOfAWay(int **lake)
{
	queue <Cell> q;
	Cell currCell;
	currCell.x = 2;
	currCell.y = 2;
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

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Incorrect number of parameters." << endl;
		cout << "Write so: pr.exe <input file> <output file>" << endl;
		return 1;
	}
	ifstream fileIn(argv[1]);
	if (!fileIn.is_open())
	{
		cout << "File " << argv[1] << " has not opened for reading.";
		return 1;
	}
	ofstream fileOut(argv[2]);
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
	int **lake = new int *[lakeSize];
	for (int i = 1; i <= lakeSize; ++i)
		lake[i] = new int[lakeSize];
	queue <Cell> islandCoords;
	CreateMatrixLake(fileIn, lake, lakeSize, islandCoords);
	for (int i = 2; i <= 1 + raftSize; ++i)
		for (int j = 2; j <= 1 + raftSize; ++j)
		{
			if (lake[i][j] == ISLAND)
			{
				cout << "Error: incorrect entrance data. On start a raft collision with the island." << endl;
				return 1;
			}
		}
	PaintTerritoryAroundIsland(lake, lakeSize, raftSize, islandCoords);
	SearchOfAWay(lake);
	if (lake[lakeSize - raftSize][lakeSize - raftSize] != 0)
		fileOut << lake[lakeSize - raftSize][lakeSize - raftSize] - 1 << endl;
	else
		fileOut << "No" << endl;
	fileIn.close();
	fileOut.close();
    return 0;
}
