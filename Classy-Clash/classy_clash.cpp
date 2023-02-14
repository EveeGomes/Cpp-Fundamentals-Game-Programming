#include <string>
#include "raylib.h"
#include "raymath.h"

#include "Prop.h"
#include "Character.h"
#include "Enemy.h"

int main() {

   // window dimensions
   int windowWidth = 384;
   int windowHeight = 384;

   InitWindow(windowWidth, windowHeight, "Classy Clash Game");

   // load the map texture
   Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
   Vector2 mapPos{ 0.0, 0.0 };
   const float mapScale = 4.f;

   // create an instance of Character class
   Character knight(windowWidth, windowHeight);

   // create a Prop instance array
   Prop props[2]{
      Prop(LoadTexture("nature_tileset/Rock.png"), Vector2{600.f, 300.f}),
      Prop(LoadTexture("nature_tileset/Log.png"), Vector2{400.f, 500.f})
   };

   // create Enemy instances
   Enemy goblin(
      Vector2{800.f, 800.f}, 
      LoadTexture("characters/goblin_idle_spritesheet.png"), 
      LoadTexture("characters/goblin_run_spritesheet.png")
   );

   Enemy slime(
      Vector2{500.f, 700.f},
      LoadTexture("characters/slime_idle_spritesheet.png"),
      LoadTexture("characters/slime_run_spritesheet.png")
   );

   // create more enemies!!!
   Enemy* enemies[]{
      &goblin,
      &slime
   };  

   for (auto enemy : enemies) {
      enemy->setTarget(&knight);
   }
   
   SetTargetFPS(60);
   while (!WindowShouldClose()) {
      BeginDrawing();
      ClearBackground(WHITE);

      // update mapPos at each frame in relation to the Character's instace
      mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

      // draw the map
      DrawTextureEx(map, mapPos, 0.0f, mapScale, WHITE);

      // render/draw the props
      for (auto prop : props) {
         prop.Render(knight.getWorldPos());
      }

      // draw the character's health or Game Over
      if (!knight.getAlive()) {
         DrawText("Game Over!", 55.f, 45.f, 40, RED);
         EndDrawing();
         continue;
      }
      else { // the character is alive
         std::string knightHealth = "Health: ";
         knightHealth.append(std::to_string(knight.getHealth()), 0, 5);
         DrawText(knightHealth.c_str(), 55.f, 45.f, 40, RED);
      }

      // update the knight
      knight.tick(GetFrameTime());

      // check map's bounds
      if (knight.getWorldPos().x < 0.f ||
         knight.getWorldPos().y < 0.f ||
         knight.getWorldPos().x + windowWidth > map.width * mapScale ||
         knight.getWorldPos().y + windowHeight > map.height * mapScale) {

         // if any of these are true, then we need to undo the character's movement
         knight.undoMovement();
      }

      // check for props collision
      for (auto prop : props) {
         if (CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec())) {
            knight.undoMovement();
         }
      }

      // update the enemies
      for (auto enemy : enemies) {
         enemy->tick(GetFrameTime());
      }

      // check for weapon collision
      if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
         for (auto enemy : enemies) {
            if (CheckCollisionRecs(enemy->getCollisionRec(), knight.getWeaponCollisionRec())) {
               enemy->setAlive(false);
            }
         }
      }

      EndDrawing();
   }
   UnloadTexture(map);
   CloseWindow();

   return 0;
}