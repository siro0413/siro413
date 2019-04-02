#pragma once



//추상클래스
class GameObject
{
public:
	GameObject() = default;
    GameObject(char* symbol, int damage, int hp, Pos pos);
    virtual ~GameObject();

    virtual void Update() = 0; //순수가상함수
    virtual void Render(); //가상함수

    auto GetSymbol() const -> const char* { return symbol; }
    void SetSymbol(char* symbol) { this->symbol = symbol; }

    auto GetDamage() const -> const int& { return damage; }
    void SetDamage(const int& damage) { this->damage = damage; }

    auto GetHp() const -> const int& { return hp; }
    void SetHp(const int& hp) { this->hp = hp; }

    auto GetPosition() const -> const Pos& { return pos; }
    void SetPosition(const Pos& pos) { this->pos = pos; }

    auto IsActive() const -> const bool& { return bActive; }
    void SetIsActive(const bool& bActive) { this->bActive = bActive; }

protected:
    char* symbol;
    int damage;
    int hp;
    Pos pos;
    bool bActive;
};