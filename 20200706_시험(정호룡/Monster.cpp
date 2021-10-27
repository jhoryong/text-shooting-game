#include "Monster.h"
#include "Map.h"
#include "MapManager.h"
#include "Core.h"
#include "ObjManager.h"
#include "Bullet.h"

CMonster::CMonster():
	m_fSpeed(5.f),
	m_iDirection(1),
	m_fShootInterval(5.f)
{
}

CMonster::~CMonster()
{
}

void CMonster::Update(float fTime)
{
	m_fX += (m_fSpeed * m_iDirection * fTime);

	CMap* pMap = CREATE_SINGLE(CMapManager)->GetCurrentMap();
	int iWidth = pMap->GetWidth();
	int iHeight = pMap->GetHeight();

	if (m_fX >= 1.f || m_fX <= -1.f)
	{
		m_tPos.X += (int)m_fX;

		if (m_tPos.X <= 1)
		{
			m_tPos.X = 1;
			m_iDirection *= -1;
		}

		else if (m_tPos.X >= iWidth - 2)
		{
			m_tPos.X = iWidth - 2;
			m_iDirection *= -1;
		}

		m_fX -= (int)m_fX;
	}

	static float fShootInterval = m_fShootInterval;
	m_fShootInterval -= fTime;

	if (m_fShootInterval <= 0.f)
	{
		m_fShootInterval = fShootInterval;
		COORD tPos = { m_tPos.X, m_tPos.Y + 1};
		CREATE_SINGLE(CObjManager)->CreateBullet(SHOOTER::Monster, tPos);
	}
}

void CMonster::Render(char* pBuffer)
{
	int iWidth = CREATE_SINGLE(CCore)->GetBufferWidth();
	memcpy(&pBuffer[m_tPos.Y * iWidth + m_tPos.X * 2], "¢¾", 2);
}
