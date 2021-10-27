#include "Bullet.h"
#include "ObjManager.h"
#include "Player.h"
#include "Core.h"
#include "Map.h"
#include "MapManager.h"
#include "Monster.h"

CBullet::CBullet() :
	m_eShooter(SHOOTER::None),
	m_fSpeed(0.f),
	m_iDirection(0)
{
	COORD tPos = CREATE_SINGLE(CObjManager)->GetPlayer()->GetPosition();
	m_tPos.X = tPos.X;
	m_tPos.Y = --(tPos.Y);
}


CBullet::~CBullet()
{
}

void CBullet::Init(SHOOTER eShooter, COORD tPos)
{
	SetShooter(eShooter);
	SetPosition(tPos);
}

void CBullet::Update(float fTime)
{
	CMap* pMap = CREATE_SINGLE(CMapManager)->GetCurrentMap();
	int iWidth = pMap->GetWidth();
	int iHeight = pMap->GetHeight();

	if (m_eShooter == SHOOTER::Player)
	{
		m_iDirection = -1;
		m_fSpeed = 3.f;
		m_fY += (m_fSpeed * m_iDirection * fTime);

		if (m_fY <= -1.f)
		{
			m_tPos.Y += (int)m_fY;

			if (m_tPos.Y <= 0) // 벽에 맞은 경우
			{
				m_bHit = true;
				m_tPos.Y = 1;
			}

			CMonster* pMonster = CREATE_SINGLE(CObjManager)->FindMonster(m_tPos);
			if (pMonster)
			{
				m_bHit = true;
				pMonster->SetHit();
			}

			m_fY -= (int)m_fY;
		}
	}

	else if (m_eShooter == SHOOTER::Monster)
	{
		m_iDirection = 1;
		m_fSpeed = 2.f;
		m_fY += (m_fSpeed * m_iDirection * fTime);

		if (m_fY >= 1.f)
		{
			m_tPos.Y += (int)m_fY;

			if (m_tPos.Y >= iHeight - 1) // 벽에 맞은 경우
			{
				m_bHit = true;
				m_tPos.Y = iHeight - 2;
			}

			CPlayer* pPlayer = CREATE_SINGLE(CObjManager)->GetPlayer();
			COORD tPos = pPlayer->GetPosition();

			if (tPos.X == m_tPos.X && tPos.Y == m_tPos.Y)
			{
				m_bHit = true;
				pPlayer->SetHit();
			}

			m_fY -= (int)m_fY;
		}
	}
	
}

void CBullet::Render(char* pBuffer)
{
	int iWidth = CREATE_SINGLE(CCore)->GetBufferWidth();
	memcpy(&pBuffer[m_tPos.Y * iWidth + m_tPos.X * 2], "＊", 2);
}
