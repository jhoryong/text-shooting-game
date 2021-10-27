#include "Core.h"
#include "MapManager.h"
#include "Map.h"
#include "ObjManager.h"
#include "Player.h"

DEFINITION_SINGLE(CCore)

CCore::CCore():
	m_pBuffer(nullptr),
	m_iBufferWidth(0),
	m_iBufferHeight(0), 

	m_iPrevTime(0),
	m_fDeltaTime(0.f)
{
}

CCore::~CCore() 
{
	SAFE_DELETE_ARRAY(m_pBuffer);

	DESTROY_SINGLE(CMapManager);

	DESTROY_SINGLE(CObjManager);
}

void CCore::Update()
{
	CREATE_SINGLE(CObjManager)->Update(m_fDeltaTime);
}

void CCore::Render()
{
	COORD tCoord = {};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), tCoord);

	CREATE_SINGLE(CMapManager)->GetCurrentMap()->CopyToBuffer(m_pBuffer);

	CREATE_SINGLE(CObjManager)->Render(m_pBuffer);

	cout << m_pBuffer << endl;
	cout << "몬스터 처치 : " << CREATE_SINGLE(CObjManager)->GetPlayer()->GetKill();
	//cout << "총알수 : " << CREATE_SINGLE(CObjManager)->m_BulletList.size();
}

bool CCore::Init()
{
	if (!CREATE_SINGLE(CMapManager)->Init())
		return false;

	return true;
}

void CCore::Run()
{
	CREATE_SINGLE(CObjManager)->Init();

	CMap* pMap = CREATE_SINGLE(CMapManager)->GetCurrentMap();
	m_iBufferWidth = pMap->GetWidth();
	m_iBufferHeight = pMap->GetHeight();

	m_iBufferWidth *= 2;
	++m_iBufferWidth;

	m_pBuffer = new char[m_iBufferWidth * m_iBufferHeight + 1];
	memset(m_pBuffer, 0, m_iBufferWidth * m_iBufferHeight + 1);

	for (int i = 0; i < m_iBufferHeight; ++i)
	{
		m_pBuffer[i * m_iBufferWidth + m_iBufferWidth - 1] = '\n';
	}


	m_iPrevTime = GetTickCount();

	while (true)
	{
		unsigned int iTime = GetTickCount();

		m_fDeltaTime = (iTime - m_iPrevTime) / 1000.f;
		m_iPrevTime = iTime;

		//system("cls");
		Update();
		Render();

		CPlayer* pPlayer = CREATE_SINGLE(CObjManager)->GetPlayer();
		if (pPlayer->GetHit() || pPlayer->GetKill() >= 3)
		{
			return;
		}
	}
}
