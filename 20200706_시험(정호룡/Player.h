#pragma once
#include "Obj.h"
class CPlayer :
    public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	int m_iKill;
	float m_fKeyPushTime;

public:
	int GetKill() {
		return m_iKill;
	}

	void KillUp() {
		++m_iKill;
	}

public:
	virtual void Update(float fTime);
	virtual void Render(char* pBuffer);
};

