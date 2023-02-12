#include "raylib.h"
#include "raymath.h"

#include "Prop.h"
#include "Character.h"
#include "Enemy.h"

int main() {

   // window dimensions array
   int winDimensions[2]{};
   winDimensions[0] = 384; // width
   winDimensions[1] = 384; // height

   // initialize the window
   InitWindow(winDimensions[0], winDimensions[1], "Classy Clash Game");

   // load the map texture
   Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png"); // firstWorldMap  OpenWorldMap24x24
   Vector2 mapPos{ 0.0, 0.0 };
   const float mapScale = 4.f;

   // create an instance of Character class
   Character knight(winDimensions[0], winDimensions[1]);

   // create a Prop instance array
   Prop props[2]{
      Prop(LoadTexture("nature_tileset/Rock.png"), Vector2{600.f, 300.f}),
      Prop(LoadTexture("nature_tileset/Log.png"), Vector2{400.f, 500.f})
   };

   // create an Enemy instance
   Enemy goblin(
      Vector2{}, 
      LoadTexture("characters/goblin_idle_spritesheet.png"), 
      LoadTexture("characters/goblin_run_spritesheet.png")
   );
   goblin.setTarget(&knight);

   SetTargetFPS(60);
   while (!WindowShouldClose()) {
      BeginDrawing();
      ClearBackground(WHITE);

      // update mapPos at each frame in relation to the Character's instace
      mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

      // draw the map
      DrawTextureEx(map, mapPos, 0.0f, mapScale, WHITE);
      // render/draw the props - using for ranged loop
      for (auto prop : props) {
         prop.Render(knight.getWorldPos());
      }

      knight.tick(GetFrameTime());

      // check map's bounds
      if (knight.getWorldPos().x < 0.f ||
         knight.getWorldPos().y < 0.f ||
         knight.getWorldPos().x + winDimensions[0] > map.width * mapScale ||
         knight.getWorldPos().y + winDimensions[1] > map.height * mapScale) {

         // if any of these are true, then we need to undo the character's movement
         knight.undoMovement();
      }

      // check for props collision
      for (auto prop : props) {
         if (CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec())) {
            knight.undoMovement();
         }
      }

      // call tick for the goblin
      goblin.tick(GetFrameTime());

      EndDrawing();
   }
   UnloadTexture(map);
   CloseWindow();

   return 0;
}