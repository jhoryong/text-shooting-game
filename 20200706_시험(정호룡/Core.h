#pragma once
#include "Game.h"

class CCore
{
	DECLARE_SINGLE(CCore)

private:
	char* m_pBuffer;
	int m_iBufferWidth;
	int m_iBufferHeight;

	unsigned int m_iPrevTime;
	float m_fDeltaTime;

public:
	int GetBufferWidth() {
		return m_iBufferWidth;
	}

private:
	void Update();
	void Render();

public:
	bool Init();
	void Run();
};

