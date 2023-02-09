#include "raylib.h"

int main() {

   // window dimensions array
   int winDimensions[2]{};
   winDimensions[0] = 384; // width
   winDimensions[1] = 384; // height

   // initialize the window
   InitWindow(winDimensions[0], winDimensions[1], "Classy Clash Game");

   // load the map texture
   Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
   float mapX{};

   SetTargetFPS(60);

   // Game while loop
   while (!WindowShouldClose()) {

      BeginDrawing();
      ClearBackground(WHITE);

      // draw the map
      Vector2 mapPos{mapX, 0.0};
      DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

      EndDrawing();
   }
   UnloadTexture(map);
   
   CloseWindow();

   return 0;
}