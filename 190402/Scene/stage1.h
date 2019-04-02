#pragma once
#include "IScene.h"

class stage1 final : public IScene
{
public:
	stage1();
	~stage1();

	// IScene��(��) ���� ��ӵ�
	void Update() override;

	void Render() override;

private:
	class Map* map;
	class Player* player;
	class Monster* monster[3];
	class Monster* monster2;
	

};

