#pragma once
#include "Game.h"

class CMap;

class CMapManager
{
	DECLARE_SINGLE(CMapManager)

private:
	CMap* m_pCurrentMap;

public:
	CMap* GetCurrentMap() {
		return m_pCurrentMap;
	}

public:
	bool Init();
	void Run();
};

