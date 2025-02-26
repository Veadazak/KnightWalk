#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H
#include "raylib.h"

class BaseCharacter
{
public:
    BaseCharacter();
    Vector2 getWorldPos() { return worldPos; }
    void undoMovement();
    Rectangle getCollissionRec();
    virtual void tick(float deltaTime);
    virtual Vector2 getScreenPos() = 0;
    //virtual void takeDamage(float damage) = 0;
    bool getAllive() { return alive; }
    void setAlive(bool isAlive) { alive = isAlive; }

protected:
    Texture2D texture{LoadTexture("textures/characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("textures/characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("textures/characters/knight_run_spritesheet.png")};
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};

    // 1 if right, -1 if left
    float rightLeft{1.f};
    // animation variables
    float runningTime{};
    int frame{};
    const int maxFrames{6};
    const float updateTime{1.f / 12.f};
    float speed{4.f};

    float width{};
    float height{};
    float scale{4.0f};

    Vector2 velocity{};

private:
    bool alive{true};
};

#endif