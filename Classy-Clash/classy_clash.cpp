#include "raylib.h"
#include "raymath.h"

int main() {

   // window dimensions array
   int winDimensions[2]{};
   winDimensions[0] = 384; // width
   winDimensions[1] = 384; // height

   // initialize the window
   InitWindow(winDimensions[0], winDimensions[1], "Classy Clash Game");

   // load the map texture
   Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
   // put this vector outside the loop so the value is saved between iterations of the loop.
   Vector2 mapPos{ 0.0, 0.0 };

   // used to scale the movement vector (direction vector)!
   float speed = 4.0;

   SetTargetFPS(60);

   // Game while loop
   while (!WindowShouldClose()) {

      BeginDrawing();
      ClearBackground(WHITE);
      
      // vector and keys to determine the direction among the map
      Vector2 direction{};
      if (IsKeyDown(KEY_A)) direction.x -= 1.0;
      if (IsKeyDown(KEY_D)) direction.x += 1.0;
      if (IsKeyDown(KEY_W)) direction.y -= 1.0;
      if (IsKeyDown(KEY_S)) direction.y += 1.0;

      // direction vector used to move the map:
      if (Vector2Length(direction) != 0.0) {
         mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), speed));
      }

      // draw the map
      DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

      EndDrawing();
   }
   UnloadTexture(map);
   
   CloseWindow();

   return 0;
}