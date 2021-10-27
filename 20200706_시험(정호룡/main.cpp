#include "Game.h"
#include "Core.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	if (!CREATE_SINGLE(CCore)->Init())
	{
		DESTROY_SINGLE(CCore);
		return 0;
	}

	CREATE_SINGLE(CCore)->Run();

	DESTROY_SINGLE(CCore);

	return 0;
}