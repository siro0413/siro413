#include "stdafx.h"
#include "./Gameobj/Player.h"
#include "./Gameobj/Monster.h"
#include "Scene/stage1.h"
//Argument Paramenter
//Argument value
//Paramenter table





int main()
{
	SceneManager::Get().AddScene("Stage1", new stage1());
	SceneManager::Get().SetCurrentScene("Stage1");

	//assert(false);
	//int a = 10, b = 20;
	//int c = Add(a, b);// ��ȯ���� ���ٸ� ������ �����ϴ� ex int c = Add<int>(a,b)


    while (true)
    {
		Sleep(50);
		SceneManager::Get().Update();
		bulletmanger::Get().Update();
		system("cls");

		bulletmanger::Get().Render();
		SceneManager::Get().Render();
	}
    return 0;
}