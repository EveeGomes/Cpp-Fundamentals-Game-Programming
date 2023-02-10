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
      DrawTextureEx(map, mapPos, 0.0f, 4.0f, WHITE);
      knight.tick(GetFrameTime());

      EndDrawing();
   }
   UnloadTexture(map);
   CloseWindow();

   return 0;
}