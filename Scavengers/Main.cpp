#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>
#include <vector>
#include <cstdlib>
#include <random>

int main()
{
    std::random_device rd;
    std::default_random_engine engine{rd()};
    std::uniform_int_distribution<int> rdmS{100, 1000};
    std::uniform_int_distribution<int> rdmT{1,2};

    const int windowWidth{1400};
    const int windowHeight{1000};
    float mapWidth{10.f};
    float mapHeight{10.f};
    InitWindow(windowWidth, windowHeight, "RPG");

    Texture2D mapa = LoadTexture("textures/NatureTileset/worldMap.png");
    Texture2D healthBar = LoadTexture("textures/characters/HealthBar.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{4.f};

    Character knight{windowWidth, windowHeight};

    // ----------------------- Tiles generation -----------------------
    std::vector<Prop> tiles;
    std::vector<Prop> grass;

    for (int x = 0; x < mapWidth; x++)
    {
        for (int y = 0; y < mapHeight; y++)
        {
            Vector2 cellPos{x, y};
            if (x == 0.f || y == 0.f || x == mapWidth - 1.f || y == mapHeight - 1.f)
            {
                Prop nextP{Vector2{32.f * mapScale * x, 32.f * mapScale * y}, LoadTexture("textures/NatureTileset/Water_mid.png"), false};
                tiles.push_back(nextP);
            }
            else
            {
                Prop nextP{Vector2{32.f * mapScale * x, 32.f * mapScale * y}, LoadTexture("textures/NatureTileset/Grass_mid.png"), true};
                tiles.push_back(nextP);
            }
        }
    }
    //-----------------------Enemy generation-----------------------
    std::vector<Enemy> enemies;
    for (int i = 0; i < 30; i++)
    {
        Enemy enemy{Vector2{rdmS(engine), rdmS(engine)}, rdmT(engine)};
        enemies.push_back(enemy);
        //enemiesP.push_back(&enemy);
    }
    std::vector<Enemy *> enemiesP;
    for (auto &enemy : enemies)
    {
        enemiesP.push_back(&enemy);
    }
    for (auto enemy : enemiesP)
    {
        enemy->setTarget(&knight);
    }
    // ----------------------- Drawing -----------------------
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        // draw the map
        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);
        DrawTextureEx(mapa, mapPos, 0.0, mapScale, WHITE);

        // draw the props

        for (auto tile : tiles)
        {
            tile.Render(knight.getWorldPos());
        }
        if (!knight.getAllive()) // Character is not alive
        {

            DrawText("Game Over!", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        else // Character is alive
        {
            // Health bar drawing
            DrawRectangle(60.f, 15.f, knight.getHeatlth(), 30.f, RED);
            std::string knightHealth = "Health: ";
            knightHealth.append(std::to_string(knight.getHeatlth()), 0, 5);
            DrawText(knightHealth.c_str(), 55.f, 45.f, 40, RED);
        }

        knight.tick(GetFrameTime());

        // Check prop collissions

        for (auto tile : tiles)
        {
            if (CheckCollisionRecs(tile.getCollissionRec(knight.getWorldPos()), knight.getCollissionRec()) && tile.passable == false)
            {
                knight.undoMovement();
            }
        }
        for (auto enemy : enemiesP)
        {
            enemy->tick(GetFrameTime());
        }
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for (auto enemy : enemiesP)
            {
                if (CheckCollisionRecs(enemy->getCollissionRec(), knight.getWeaponConllissionRec()))
                {
                    enemy->setAlive(false);
                }
            }
        }
        EndDrawing();
    }
    CloseWindow();
}