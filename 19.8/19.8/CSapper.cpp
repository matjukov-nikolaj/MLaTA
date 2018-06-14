#include "stdafx.h"
#include "CSapper.h"


CSapper::CSapper(std::istream & input, std::ostream & output)
	:m_input(input)
	, m_output(output)
{
	ReadField();
}

void CSapper::PrintField()
{
	CalculateMins();
	for (int i = 1; i < m_row; ++i)
	{
		for (int j = 1; j < m_col; ++j)
		{
			if (m_field[i][j] == -1)
			{
				m_output << "*";
			}
			else
			{
				m_output << m_field[i][j];
			}
		}
		m_output << "\n";
	}
}

void CSapper::ReadField()
{
	m_input >> m_row >> m_col;

	if ((m_row < 0 || m_row > 10) || (m_col < 0 || m_col > 10))
	{
		throw std::invalid_argument("Invalid argument!");
	}
	m_row += 2;
	m_col += 2;

	ResizeVector();
	m_row--;
	m_col--;
	char ch = ' ';
	for (int i = 1; i < m_row; ++i)
	{
		for (int j = 1; j < m_col; ++j)
		{
			m_input >> ch;
			if (ch == '*')
			{
				m_field[i][j] = -1;
			}
			else if (ch == '+')
			{
				m_field[i][j] = -2;
			}
			else
			{
				throw std::logic_error("Incorrect input data.");
			}
		}
	}
}


void CSapper::Metka(int i, int j, int & currCounter)
{
	if ((m_field[i + 1][j] == -1))
	{
		currCounter++;
	}
	if ((m_field[i - 1][j] == -1))
	{
		currCounter++;
	}
	if ((m_field[i][j + 1] == -1))
	{
		currCounter++;
	}
	if ((m_field[i][j - 1] == -1))
	{
		currCounter++;
	}
	if ((m_field[i + 1][j + 1] == -1))
	{
		currCounter++;
	}
	if ((m_field[i + 1][j - 1] == -1))
	{
		currCounter++;
	}
	if ((m_field[i - 1][j + 1] == -1))
	{
		currCounter++;
	}
	if ((m_field[i - 1][j - 1] == -1))
	{
		currCounter++;
	}
}

void CSapper::CalculateMins()
{
	int currCounter = 0;
	for (int i = 1; i < m_row; ++i)
	{
		for (int j = 1; j < m_col; ++j)
		{
			if (m_field[i][j] == -2)
			{
				Metka(i, j, currCounter);
				m_field[i][j] = currCounter;
				currCounter = 0;
			}
		}
	}
}

void CSapper::ResizeVector()
{
	m_field.resize(m_row);
	for (int i = 0; i < m_row; ++i)
		m_field[i].resize(m_col);
}

