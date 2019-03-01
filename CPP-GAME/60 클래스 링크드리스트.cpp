#include <iostream>

using namespace std;

class CListNode
{
public:
	CListNode()
	{

	}
	~CListNode()
	{

	}

public:
	int			m_iData;
	CListNode*	m_pNext;
	CListNode*	m_pPrev;
};

class CList
{
private:
	CListNode*	m_pBegin;
	CListNode*	m_pEnd;
	int			m_iSize;

public:
	CList()
	{
		m_pBegin = new CListNode;
		m_pEnd = new CListNode;

		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;

		m_iSize = 0;
	}

	~CList()
	{
		clear();
		delete m_pBegin;
		delete m_pEnd;
	}

	void push_back(int iData)
	{
		CListNode* pNode = new CListNode;
		pNode->m_iData = iData;

		CListNode* pPrev = m_pEnd->m_pPrev;

		pPrev->m_pNext = pNode;
		pNode->m_pPrev = pPrev;

		pNode->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = pNode;

		++m_iSize;
	}

	bool empty()
	{
		return m_iSize == 0;
	}

	void clear()
	{
		CListNode* pNode = m_pBegin->m_pNext;
		while (pNode != m_pEnd)
		{
			CListNode* pNext = pNode->m_pNext;
			delete pNode;
			pNode = pNext;
		}
		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;
		m_iSize = 0;
	}

	int pop_back()
	{
		CListNode* pNode = m_pEnd->m_pPrev;
		
		if (pNode == m_pBegin)
			return INT_MAX;
		
		int result = pNode->m_iData;

		pNode->m_pPrev->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = pNode->m_pPrev;

		delete pNode;

		--m_iSize;

		return result;
	}
};

int main()
{
	CList list;
	
	for (int i = 0; i < 100; ++i)
	{
		list.push_back(i);
	}

	while (!list.empty())
	{
		cout << list.pop_back() << endl;
	}
}