#include "Player.h"
#include "MapManager.h"
#include "Map.h"
#include "Core.h"
#include "Bullet.h"
#include "ObjManager.h"

CPlayer::CPlayer() :
	m_iKill(0),
	m_fKeyPushTime(0.2f)
{
} 

CPlayer::~CPlayer()
{
}

void CPlayer::Update(float fTime)
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_fX -= (10.f * fTime);
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_fX += (10.f * fTime);
	}

	CMap* pMap = CREATE_SINGLE(CMapManager)->GetCurrentMap();
	int iWidth = pMap->GetWidth();
	int iHeight = pMap->GetHeight();

	if (m_fX >= 1.f || m_fX <= -1.f)
	{
		m_tPos.X += (int)m_fX;

		if (m_tPos.X <= 1)
			m_tPos.X = 1;

		else if (m_tPos.X >= iWidth - 2)
			m_tPos.X = iWidth - 2;

		m_fX -= (int)m_fX;
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		static float fKeyPushTime = m_fKeyPushTime;
		m_fKeyPushTime -= fTime;

		if (m_fKeyPushTime <= 0.f)
		{
			m_fKeyPushTime = fKeyPushTime;
			COORD tPos = { m_tPos.X, m_tPos.Y - 1 };
			CREATE_SINGLE(CObjManager)->CreateBullet(SHOOTER::Player, tPos);
		}
	}
}

void CPlayer::Render(char* pBuffer)
{
	int iWidth = CREATE_SINGLE(CCore)->GetBufferWidth();
	memcpy(&pBuffer[m_tPos.Y * iWidth + m_tPos.X * 2], "¢À", 2);
}
