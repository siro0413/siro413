#include "stdafx.h"
#include "Player.h"
#include "system/bullet.h"
#define UP 224 72
#define Down 224 80
#define Left 224 75
#define Right 224 77


Player::Player(char * symbol, int damage, int hp, Pos pos)
    : GameObject(symbol, damage, hp, pos)
{
}

Player::~Player()
{
  
}

void Player::Update()
{
	if (GetAsyncKeyState('W') & 0x8000)
		pos.y--;
	else if (GetAsyncKeyState('S') & 0x8000)
		pos.y++;
	if (GetAsyncKeyState('A') & 0x8000)
		pos.x--;
	else if (GetAsyncKeyState('D') & 0x8000)
		pos.x++;

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		//for (int i = 0; i < 5; i++)
		//{
		//	if (!bullets[i].bFire)
		//	{
		//		bullets[i].pos = pos; //�Ѿ˹߻���ġ�� player��ǥ
		//		bullets[i].bFire = true; //�Ѿ˹߽�
		//		break;//�ѹ߽���� Ż�� 5�ߵ��ÿ� �����ʰ� �ϱ�����break�ɱ�
		//	}
		//}

		//����
		//bullet bullet;
		//bullet.pos = pos;
		//bullet.bFire = true;
		//bullets.push_back(bullet);

		//bullets.emplace_back(pos, true);
		
		bulletmanger::Get().AddBullet(pos);

	}

	//for (int i = 0; i < bullets.size(); i++)
	//	bullets[i].Updete();

	//for (int i = 0; i < 5; i++)
	//	bullets[i].Updete();

	//Range based for loop ��������� for ��
	//for (bullet& bullet : bullets)
	//	bullet.Updete();//����� ����Ʈ ���� ����
}

void Player::Render()
{

	//for (int i = 0; i < bullets.size(); i++)
	//	bullets[i].Render();
	
	Renderer::Get().Render(this);
}
//GetAsyncKeyState vs getkeysate
//0x8000
//virtual keycode