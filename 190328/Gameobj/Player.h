#pragma once
#include "GameObject.h"
//#include "system/bullet.h"



class Player final : public GameObject
{
public:
    
    Player(char* symbol, int damage, int hp, Pos pos/* = {3, 3}*/);//default parameter
    ~Player();

    void Update() override;
	void Render() override;

private:
    friend class Collision;
	//std::vector<class bullet>bullets;
};