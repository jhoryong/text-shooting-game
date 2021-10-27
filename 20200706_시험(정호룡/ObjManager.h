#pragma once
#include "Game.h"

class CPlayer;
class CMonster;
class CBullet;

class CObjManager
{
	friend class CCore;

	DECLARE_SINGLE(CObjManager)

private:
	vector<CMonster*> m_vecMonster;
	CPlayer* m_pPlayer;
	list<CBullet*> m_BulletList;

public:
	CPlayer* GetPlayer() {
		return m_pPlayer;
	}

public:
	CMonster* FindMonster(COORD tPos);
	void CreateBullet(SHOOTER eShooter, COORD tPos);

public:
	void Init();
	void Update(float fTime);
	void Render(char* pBuffer);
};

