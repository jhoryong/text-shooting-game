#pragma once
#include "Game.h"

class CObj
{
public:
	CObj();
	virtual ~CObj() = 0;

protected:
	COORD m_tPos;
	float m_fX;
	float m_fY;
	bool m_bHit;

public:
	void SetPosition(const COORD& tPos) {
		m_tPos.X = tPos.X; m_tPos.Y = tPos.Y;
	}

	COORD& GetPosition() {
		return m_tPos;
	}

	bool GetHit() {
		return m_bHit;
	}

	void SetHit() {
		m_bHit = true;
	}

public:
	virtual void Update(float fTime) = 0;
	virtual void Render(char* pBuffer) = 0;
};

