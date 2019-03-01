#pragma once

#include "value.h"

class CFileStream
{
public:
	CFileStream();
	~CFileStream();

private:
	FILE*	m_pFile;
	int		m_iFileSize;
	bool	m_bOpen;

public:
	bool Open(char* pFileName, char* pMode);
	bool Close();
	void Read(void* pData, int iSize);
	void ReadLine(void* pData, int& iSize); // 한줄이 몇바이트인지 알려주는 함수
	void Write(void* pData, int iSize);
	void WriteLine(void* pData, int iSize);
};

