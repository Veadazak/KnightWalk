#ifndef ENEMY_H
#define ENEMY_H
#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy: public BaseCharacter
{
public:
    Enemy(Vector2 pos, int type);
    virtual void tick(float deltaTime) override;
    void setTarget(Character* character) { target = character;}
    virtual Vector2 getScreenPos() override;
private:
    Character* target;
    float damagePerSec{10.f};
    float minRadius{25.f};
    float chaseRadius{400.f};
};
#endif