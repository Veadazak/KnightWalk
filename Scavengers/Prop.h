#include "raylib.h"
class Prop
{
public:
    Prop(Vector2 pos, Texture2D tex, bool pas);
    void Render(Vector2 knightPos);
    Rectangle getCollissionRec(Vector2 knightPos);
    bool passable{true};
private:
    Texture2D texture{};
    Vector2 worldPos{};
    float scale{4.f};
};