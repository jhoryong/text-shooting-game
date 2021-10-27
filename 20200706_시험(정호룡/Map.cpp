#include "Map.h"
#include "Core.h"

CMap::CMap():
	m_pBlock(nullptr),
	m_iWidth(0),
	m_iHeight(0),
	m_tStartPos{}
{
}

CMap::~CMap()
{
	for (int i = 0; i < m_iHeight; ++i)
	{
		SAFE_DELETE_ARRAY(m_pBlock[i]);
	}

	SAFE_DELETE_ARRAY(m_pBlock);
}

bool CMap::Init(const char* pFileName)
{
	FILE* pFile = nullptr;
	fopen_s(&pFile, pFileName, "rt");

	if (!pFile)
		return false;

	char cLine[256] = {};
	fgets(cLine, 256, pFile);

	char* pContext = nullptr;
	char* pReturn = strtok_s(cLine, ", ", &pContext);

	m_iWidth = atoi(pReturn);
	m_iHeight = atoi(pContext);

	m_pBlock = new char* [m_iHeight];

	for (int i = 0; i < m_iHeight; i++)
	{
		m_pBlock[i] = new char[m_iWidth + 2];

		memset(m_pBlock[i], 0, m_iWidth + 2);
		memset(cLine, 0, m_iWidth + 2);

		fgets(cLine, 256, pFile);

		memcpy(m_pBlock[i], cLine, m_iWidth + 2);
	}

	m_tStartPos.X = m_iWidth / 2;
	m_tStartPos.Y = m_iHeight - 2;

	fclose(pFile);
	return true;
}

void CMap::CopyToBuffer(char* pBuffer)
{
	for (int i = 0; i < m_iHeight; ++i)
	{
		for (int j = 0; j < m_iWidth; ++j)
		{
			switch ((BLOCK)m_pBlock[i][j])
			{
			case BLOCK::Space:
				memcpy(&pBuffer[i * (m_iWidth * 2 + 1) + j * 2], "  ", 2);
				break;

			case BLOCK::Wall:
				memcpy(&pBuffer[i * (m_iWidth * 2 + 1) + j * 2], "бс", 2);
				break;
			}
		}
	}		
}
