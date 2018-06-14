#pragma once
class CSapper
{
public:
	CSapper(std::istream & input, std::ostream & output);
	void PrintField();

private:

	void ReadField();
	void Metka(int i, int j, int & currCounter);
	void CalculateMins();
	void ResizeVector();

	std::vector<std::vector<int>> m_field;

	int m_row;
	int m_col;

	std::istream &m_input;
	std::ostream &m_output;
};

