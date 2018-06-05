#include "stdafx.h"
#include "CMaxWay.h"


CMaxWay::CMaxWay(std::istream & input, std::ostream & output)
	:m_input(input)
	, m_output(output)
{
	ReadGraph();
}

void CMaxWay::OneIterationOfTheTable(std::vector<int> &table, std::vector<int> &path, NegativeCycle &cycle)
{
	int firstNode = 0;
	int secondNode = 0;
	int tempCost = 0;

	for (int j = 0; j < m_numberArcs; ++j)
	{
		firstNode = m_arcs[j].firstNode;
		secondNode = m_arcs[j].secondNode;
		tempCost = table[firstNode] + m_arcs[j].cost;

		if ((table[firstNode] > INT_MIN)
			&& (table[secondNode] < tempCost))
		{
			table[secondNode] = std::min(INT_MAX, tempCost);
			path[secondNode] = firstNode;
			cycle.node = secondNode;
			cycle.isNegative = true;
		}
	}
}

std::vector<int> CMaxWay::GetNegativePath(const std::vector<int> &path, NegativeCycle &cycle)
{
	std::vector<int> negativePath;
	negativePath.push_back(cycle.node + 1);
	int currNode = path[cycle.node];

	while (currNode != cycle.node)
	{
		negativePath.push_back(currNode + 1);
		currNode = path[currNode];
	}

	negativePath.push_back(currNode + 1);
	return negativePath;
}

std::vector<int> CMaxWay::GetPath(const std::vector<int> &table, const std::vector<int> & path, int node)
{
	std::vector<int> maxPath;
	int currNode = 0;
	currNode = node;

	while (currNode != 0)
	{
		maxPath.push_back(currNode + 1);
		currNode = path[currNode];
	}

	maxPath.push_back(m_firstNode);
	return maxPath;
}

void CMaxWay::PrintPath(const std::vector<int> &path, bool isNegative)
{
	if (isNegative)
	{
		m_output << "No" << "\n";
	}

	m_output << path.size() << " ";
	std::copy(path.rbegin(), path.rend(), std::ostream_iterator<int>(m_output, " "));
	m_output << "\n";
}

void CMaxWay::MaxWaysToNodes(const std::vector<int> &table, const std::vector<int> &path)
{
	std::vector<int> maxPath;
	int currNode = 0;
	for (int i = 0; i < m_numberNodes; ++i)
	{
		if (table[i] == INT_MIN)
		{
			m_output << "No" << "\n";
			continue;
		}
		maxPath = GetPath(table, path, i);
		m_output << table[i] << " ";
		PrintPath(maxPath, false);
	}
}

void CMaxWay::GetSolution()
{
	std::vector<int> maxDistsTable(m_numberNodes, INT_MIN);
	maxDistsTable[m_firstNode - 1] = 0;
	std::vector<int> path(m_numberNodes);
	NegativeCycle cycle;

	for (int i = 0; i < m_numberNodes; ++i)
	{
		cycle.isNegative = false;
		OneIterationOfTheTable(maxDistsTable, path, cycle);
	}

	if (cycle.isNegative)
	{
		std::vector<int> negativePath = GetNegativePath(path, cycle);
		PrintPath(GetNegativePath(path, cycle), true);
	}
	else
	{
		MaxWaysToNodes(maxDistsTable, path);
	}
}

void CMaxWay::ReadGraph()
{
	m_input >> m_numberNodes >> m_numberArcs >> m_firstNode;

	if ((m_numberNodes <= 3 || m_numberNodes >= 1000) || (m_numberArcs <= 3 || m_numberArcs >= 500000))
	{
		throw std::invalid_argument("Invalid argument!");
	}

	Arc arc;
	for (int i = 0; i < m_numberArcs; ++i)
	{
		m_input >> arc.firstNode >> arc.secondNode >> arc.cost;
		arc.firstNode--;
		arc.secondNode--;
		m_arcs.push_back(arc);
	}
}


