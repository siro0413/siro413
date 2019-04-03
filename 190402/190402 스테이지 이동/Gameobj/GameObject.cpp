#include "stdafx.h"
#include "GameObject.h"
#include "../system/Renderer.h"


GameObject::GameObject(char * symbol, int damage, int hp, Pos pos)
    : symbol(symbol)
    , damage(damage)
    , hp(hp)
    , pos(pos)
{    
}

GameObject::~GameObject()
{
   
}

void GameObject::Render()
{
    Renderer::Get().Render(this);
}
