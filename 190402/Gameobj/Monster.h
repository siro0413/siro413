#pragma once
#include "GameObject.h"
// enum���� Ÿ�Ե� ���Ҽ��ִ�
enum class MonDirect : unsigned long
{
	Up,Right,Down,Left

};



class Monster final : public GameObject
{
public:
	Monster()=default;
    Monster(char* symbol, int damage, int hp, Pos pos);
    virtual ~Monster();

	void Initialize(char* symbol, int damage, int hp, Pos pos);

    void Update() override;

private:
    friend class Collision;

	MonDirect direction;
	DWORD time;
	//DWORd = unsingend long
};