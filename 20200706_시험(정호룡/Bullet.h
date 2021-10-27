#pragma once
#include "Obj.h"
class CBullet :
    public CObj
{
public:
    CBullet();
    virtual ~CBullet();

private:
    SHOOTER m_eShooter;
    float m_fSpeed;
    int m_iDirection;

public:
    void SetShooter(SHOOTER eShooter) {
        m_eShooter = eShooter;
    }

public:
    void Init(SHOOTER eShooter, COORD tPos);
    virtual void Update(float fTime);
    virtual void Render(char* pBuffer);
};

