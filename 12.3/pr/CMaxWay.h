#pragma once
class CMaxWay
{
	struct Arc
	{
		int firstNode = 0;
		int secondNode = 0;
		int cost = 0;
	};

	struct NegativeCycle
	{
		int node;
		int isNegative;
	};

public:
	CMaxWay(std::istream & input, std::ostream & output);
	void GetSolution();

private:
	void ReadGraph();

	void OneIterationOfTheTable(std::vector<int> &table, std::vector<int> &path, NegativeCycle &cycle);
	std::vector<int> GetNegativePath(const std::vector<int>& path, NegativeCycle & cycle);
	std::vector<int> GetPath(const std::vector<int>& table, const std::vector<int>& path, int node);
	void PrintPath(const std::vector<int>& path, bool isNegative);
	void MaxWaysToNodes(const std::vector<int>& table, const std::vector<int>& path);


	int m_numberNodes = 0;
	int m_numberArcs = 0;
	int m_firstNode = 0;

	std::vector<Arc> m_arcs;
	
	std::istream &m_input;
	std::ostream &m_output;

};

