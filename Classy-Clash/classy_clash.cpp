#include "raylib.h"
#include "raymath.h"

#include "Character.h"

int main() {

   // window dimensions array
   int winDimensions[2]{};
   winDimensions[0] = 384; // width
   winDimensions[1] = 384; // height

   // initialize the window
   InitWindow(winDimensions[0], winDimensions[1], "Classy Clash Game");

   // load the map texture
   Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
   Vector2 mapPos{ 0.0, 0.0 };
   const float mapScale = 4.f;

   // create an instance of Character class
   Character knight;
   knight.setScreenPos(winDimensions[0], winDimensions[1]);

   SetTargetFPS(60);
   while (!WindowShouldClose()) {
      BeginDrawing();
      ClearBackground(WHITE);

      // update mapPos at each frame in relation to the Character's instace
      mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

      // draw the map
      DrawTextureEx(map, mapPos, 0.0f, mapScale, WHITE);
      knight.tick(GetFrameTime());

      /*
      * In tick we're setting the m_worldPos, so we need to check the map bounds AFTER tick is called.
      */
      // check map's bounds
      if (knight.getWorldPos().x < 0.f ||
         knight.getWorldPos().y < 0.f ||
         knight.getWorldPos().x + winDimensions[0] > map.width * mapScale ||
         knight.getWorldPos().y + winDimensions[1] > map.height * mapScale) {

         // if any of these are true, then we need to undo the character's movement! We do this by storing the m_worldPos of the last frame
         knight.undoMovement();
      }

      EndDrawing();
   }
   UnloadTexture(map);
   CloseWindow();

   return 0;
}