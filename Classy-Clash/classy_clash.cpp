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

   // load the knight character
   Texture2D knight = LoadTexture("characters/knight_idle.spritesheet.png");
   Vector2 knightPos{
      (float)winDimensions[0] / 2.0f - 4.0f * (0.5f * (float)knight.width / 6.0f), // windows width - half of knight.width divided by 6 as the sprite sheet as 6 images.
      (float)winDimensions[1] / 2.0f - 4.0f * (0.5f * (float)knight.height)
   };
   // we'll use DrawTexturePro for drawing this texture because with this function we can scale the image (since it's really small)
   // so, in the knightPos vector, we'll multiply the knight.width and knight.height whole parenthesis by 4.0

   SetTargetFPS(60);
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