#pragma once
#include "Game.h"

class CMap
{
	friend class CMapManager;

private:
	CMap();
	~CMap();

private:
	char** m_pBlock;
	int m_iWidth;
	int m_iHeight;
	COORD m_tStartPos;

public: /* GET() */
	int GetWidth() {
		return m_iWidth;
	}

	int GetHeight() {
		return m_iHeight;
	}

	COORD& GetStartPos() {
		return m_tStartPos;
	}

	BLOCK GetBlock(COORD& tPos) {
		return (BLOCK)m_pBlock[tPos.Y][tPos.X];
	}

public: /* SET() */
	void SetBlock(COORD& tPos, BLOCK eBlock) {
		m_pBlock[tPos.Y][tPos.X] = (char)eBlock;
	}

public:
	bool Init(const char* pFileName);
	void CopyToBuffer(char* pBuffer);
};

