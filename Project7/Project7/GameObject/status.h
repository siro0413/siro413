#include "stdafx.h"
#pragma once

class status
{
public:
	status();
	virtual ~status();

	virtual void Update() = 0;
	virtual void Render();

	auto GetSymbol() const -> const char* { return symbol; }
	void SetSymbol(char* symbol) { this->symbol = symbol; }

	auto GetDamage() const -> const int& { return att; }
	void SetDamage(const int& damage) { this->att = att; }

	auto GetHp() const -> const int& { return hp; }
	void SetHp(const int& hp) { this->hp = hp; }

	auto GetPosition() const -> const Pos& { return pos; }
	void SetPosition(const Pos& pos) { this->pos = pos; }

	auto IsActive() const -> const bool& { return bActive; }
	void SetIsActive(const bool& bActive) { this->bActive = bActive; }

private:
	int hp;
	int att=1;
	char* symbol;
	Pos pos;
	bool bActive;



};
