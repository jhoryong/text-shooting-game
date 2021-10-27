#include "MapManager.h"
#include "Map.h"

DEFINITION_SINGLE(CMapManager)

CMapManager::CMapManager():
	m_pCurrentMap(nullptr)
{}

CMapManager::~CMapManager()
{
	SAFE_DELETE(m_pCurrentMap);
}

bool CMapManager::Init()
{
	CMap* pMap = new CMap;

	if (!pMap->Init("map.txt"))
	{
		SAFE_DELETE(pMap);
		return false;
	}

	m_pCurrentMap = pMap;

	return true;
}

void CMapManager::Run()
{
}
