#include "stdafx.h"
#include "CMultiplicationGame.h"

CMultiplicationGame::CMultiplicationGame(std::istream & input, std::ostream & output)
	:m_input(input)
	,m_output(output)
{
}

void CMultiplicationGame::PrintWinnersLIst()
{
	std::vector<unsigned> winnersList = GetWinnersList();
	std::copy(winnersList.begin(), winnersList.end(), std::ostream_iterator<unsigned>(m_output, "\n"));
}

void CMultiplicationGame::GetNumberOfPartiesList()
{
	unsigned N = 0;
	unsigned M = 0;
	m_input >> M;
	for (unsigned i = 0; i < M; ++i)
	{
		m_input >> N;
		if (10000 < N || N < 2)
		{
			throw std::out_of_range("Invalid N.");
		}
		m_NNumbers.push_back(N);
	}
}

std::vector<unsigned> CMultiplicationGame::GetWinnersList()
{
	GetNumberOfPartiesList();
	std::vector<unsigned> winnersList;
	unsigned P = 1;
	for (unsigned N : m_NNumbers)
	{
		winnersList.push_back(GetResultOfTheRound(P, N));
		P = 1;
	}
	return winnersList;
}

unsigned CMultiplicationGame::GetResultOfTheRound(const unsigned &P, unsigned N)
{
	unsigned iteration = 0;
	double tempResult = static_cast<double>(N);
	while (tempResult > P)
	{
		tempResult = iteration % 2 == 0 ? tempResult / 5 : tempResult / 2;
		iteration++;
	}
	return iteration % 2 == 0 ? 2 : 1;
}
