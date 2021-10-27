#pragma once

#define	CRTDBG_MAP_ALLOC

#include <iostream>
#include <Windows.h>
#include <vector>
#include <list>
#include <unordered_map>
#include <time.h>
#include <crtdbg.h>

using namespace std;

enum class SHOOTER
{
	None,
	Player,
	Monster
};

enum class BLOCK
{
	Space = '0',
	Wall = '1',
};



#define		NAME_SIZE			64

#ifdef _DEBUG
#define	new		new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif // _DEBUG

#define	SAFE_DELETE(p)	if(p)	{ delete p; p = nullptr; }
#define	SAFE_DELETE_ARRAY(p)	if(p)	{ delete[] p; p = nullptr; }

#define	SAFE_DELETE_VECLIST(p)	\
{\
	auto		iter = p.begin();\
	auto		iterEnd = p.end();\
	for(; iter != iterEnd; ++iter)\
	{\
		SAFE_DELETE((*iter));\
	}\
	p.clear();\
}

template <typename T>
void Safe_Delete_VecList(T& p)
{
	auto		iter = p.begin();
	auto		iterEnd = p.end();
	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE((*iter));
	}

	p.clear();
}

#define	DECLARE_SINGLE(Type)	\
private:\
	static Type*		m_pInst;\
public:\
	static Type* GetInst()\
	{\
		if(!m_pInst)\
			m_pInst = new Type;\
		return m_pInst;\
	}\
	static void DestroyInst()\
	{\
		SAFE_DELETE(m_pInst);\
	}\
private:\
	Type();\
	~Type();

#define	DEFINITION_SINGLE(Type)	Type* Type::m_pInst = nullptr;
#define	CREATE_SINGLE(Type)	Type::GetInst()
#define	DESTROY_SINGLE(Type)	Type::DestroyInst()
