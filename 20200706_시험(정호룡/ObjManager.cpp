#include "ObjManager.h"
#include "Player.h"
#include "MapManager.h"
#include "Map.h"
#include "Monster.h"
#include "Bullet.h"

DEFINITION_SINGLE(CObjManager)

CObjManager::CObjManager():
	m_pPlayer(nullptr)
{}

CObjManager::~CObjManager()
{
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE_VECLIST(m_vecMonster);
	SAFE_DELETE_VECLIST(m_BulletList);
}

CMonster* CObjManager::FindMonster(COORD tPos)
{
	auto iter = m_vecMonster.begin();
	auto iterEnd = m_vecMonster.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetPosition().X == tPos.X && (*iter)->GetPosition().Y == tPos.Y)
		{
			return (*iter);
		}
	}

	return nullptr;
}

void CObjManager::CreateBullet(SHOOTER eShooter, COORD tPos)
{
	CBullet* pBullet = new CBullet;
	pBullet->Init(eShooter, tPos);
	m_BulletList.push_back(pBullet);
}

void CObjManager::Init()
{
	m_pPlayer = new CPlayer;
	m_pPlayer->SetPosition(CREATE_SINGLE(CMapManager)->GetCurrentMap()->GetStartPos());

	for (int i = 0; i < 3; ++i)
	{
		CMonster* pMonster = new CMonster;

		COORD tPos = { static_cast<short>(i * 2.5), static_cast<short>(i + 1)};

		pMonster->SetPosition(tPos);

		m_vecMonster.push_back(pMonster);
	}
}

void CObjManager::Update(float fTime)
{
	m_pPlayer->Update(fTime);

	auto iter = m_vecMonster.begin();
	auto iterEnd = m_vecMonster.end();

	for (; iter != iterEnd;)
	{
		if ((*iter)->GetHit())
		{
			SAFE_DELETE((*iter));
			iter = m_vecMonster.erase(iter);
			iterEnd = m_vecMonster.end();
			CREATE_SINGLE(CObjManager)->GetPlayer()->KillUp();
			continue;
		}

		(*iter)->Update(fTime);
		++iter;
	}
	
	auto Listiter = m_BulletList.begin();
	auto ListIterEnd = m_BulletList.end();

	for (; Listiter != ListIterEnd;)
	{
		if ((*Listiter)->GetHit())
		{
			SAFE_DELETE((*Listiter));
			Listiter = m_BulletList.erase(Listiter);
			ListIterEnd = m_BulletList.end();
			continue;
		}

		(*Listiter)->Update(fTime);
		++Listiter;
	}
}

void CObjManager::Render(char* pBuffer)
{
	m_pPlayer->Render(pBuffer);

	auto iter = m_vecMonster.begin();
	auto iterEnd = m_vecMonster.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->Render(pBuffer);
	}

	auto iterList = m_BulletList.begin();
	auto iterListEnd = m_BulletList.end();

	for (; iterList != iterListEnd; ++iterList)
	{
		(*iterList)->Render(pBuffer);
	}
}
