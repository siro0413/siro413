#pragma once



//�߻�Ŭ����
class GameObject
{
public:
	GameObject() = default;
    GameObject(char* symbol, int damage, int hp, Pos pos);
    virtual ~GameObject();

    virtual void Update() = 0; //���������Լ�
    virtual void Render(); //�����Լ�

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