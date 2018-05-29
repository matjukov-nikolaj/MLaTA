#pragma once
class CMultiplicationGame
{
public:
	CMultiplicationGame(std::istream & input, std::ostream & output);
	void PrintWinnersLIst();
private:
	void GetNumberOfPartiesList();
	std::vector<unsigned> GetWinnersList();
	unsigned GetResultOfTheRound(const unsigned &P, unsigned N);
	
	std::vector<unsigned> m_NNumbers;
	std::istream &m_input;
	std::ostream &m_output;

	const unsigned MIN_VALUE = 2;
	const unsigned MAX_VALUE = 5;
};

