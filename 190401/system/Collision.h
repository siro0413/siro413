#pragma once

class Collision
{
public:
    static const bool IsInside(class Player* player, class Monster* monster);
    static const bool IsIntersect(class Player* player, class Monster* monster);
};