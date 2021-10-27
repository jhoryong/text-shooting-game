#pragma once
#include "Obj.h"
class CMonster :
    public CObj
{
public:
    CMonster();
    virtual ~CMonster();

private:
    float m_fSpeed;
    int m_iDirection;
    float m_fShootInterval;

public:
    virtual void Update(float fTime);
    virtual void Render(char* pBuffer);
};

