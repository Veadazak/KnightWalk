#include "Prop.h"
#include "raymath.h"

Prop::Prop(Vector2 pos, Texture2D tex,bool pas) : 
    worldPos(pos),
    texture(tex),
    passable(pas)
{
    
}
void Prop::Render(Vector2 knightPos)
{
    Vector2 screenPos {Vector2Subtract(worldPos,knightPos)};
    DrawTextureEx(texture,screenPos,0.f,scale,WHITE);
}

Rectangle Prop::getCollissionRec(Vector2 knightPos)
{
    Vector2 screenPos {Vector2Subtract(worldPos,knightPos)};
    return Rectangle{
        screenPos.x,
        screenPos.y,
        texture.width*scale,
        texture.height*scale
    };
}