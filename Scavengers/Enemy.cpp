#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, int type)

{
    worldPos = pos;
    if (type == 1)
    {
        texture =  LoadTexture("textures/characters/goblin_idle_spritesheet.png");
        idle =  LoadTexture("textures/characters/goblin_idle_spritesheet.png");
        run = LoadTexture("textures/characters/goblin_run_spritesheet.png");
    }
    else if (type ==2)
    {
        texture = LoadTexture("textures/characters/slime_idle_spritesheet.png");
        idle = LoadTexture("textures/characters/slime_idle_spritesheet.png");
        run = LoadTexture("textures/characters/slime_run_spritesheet.png");
    }
    width = texture.width / maxFrames;
    height = texture.height;
    speed = 2.5f;
}

void Enemy::tick(float deltaTime)
{
    if (!getAllive())
        return;
    // get toTarget
    
    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());
    if(Vector2Length(velocity)>chaseRadius){
        velocity={};
    }
    else if (Vector2Length(velocity) < minRadius)
    {
        velocity = {};
    }
    BaseCharacter::tick(deltaTime);

    if (CheckCollisionRecs(getCollissionRec(), target->getCollissionRec()))
    {
        target->takeDamage(damagePerSec * deltaTime);
    }
}

Vector2 Enemy::getScreenPos()
{
    return Vector2Subtract(worldPos, target->getWorldPos());
}
