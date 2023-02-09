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
   Vector2 mapPos{ 0.0, 0.0 };
   // used to scale the movement vector (direction vector)!
   float speed = 4.0;

   // load the knight character
   Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
   Vector2 knightPos{
      (float)winDimensions[0] / 2.0f - 4.0f * (0.5f * (float)knight.width / 6.0f),
      (float)winDimensions[1] / 2.0f - 4.0f * (0.5f * (float)knight.height)
   };
   // determines the direction of the sprite; the convention => 1: facing right, -1: facing left
   float rightLeft = 1.f;

   // animation variables
   float runningTime{};
   int frame{}; // current animation frame from the spritesheet
   const int maxFrames = 6;
   const float updateTime = 1.f / 12.f;


   SetTargetFPS(60);
   while (!WindowShouldClose()) {
      const float dT = GetFrameTime();

      BeginDrawing();
      ClearBackground(WHITE);
      
      // vector and keys to determine the direction among the map
      Vector2 direction{};
      if (IsKeyDown(KEY_A)) direction.x -= 1.0f;
      if (IsKeyDown(KEY_D)) direction.x += 1.0f;
      if (IsKeyDown(KEY_W)) direction.y -= 1.0f;
      if (IsKeyDown(KEY_S)) direction.y += 1.0f;

      // direction vector used to move the map:
      if (Vector2Length(direction) != 0.0f) {
         mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), speed));
         // set the rightLeft variable here:
         direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
      }

      // draw the map
      DrawTextureEx(map, mapPos, 0.0f, 4.0f, WHITE);

      // update animation frame
      runningTime += dT;
      if (runningTime >= updateTime) {
         frame++;
         runningTime = 0.f;
         if (frame > maxFrames) frame = 0;
      }

      // draw the character
      // this source rectangle is where we choose the animation frame. The x component determines which frame to choose... So, we'll replace the x value of 0.f to   frame * (float)knight.width/6.f; this allows us to select the frame from the spritesheet
      Rectangle srcK{ frame * (float)knight.width / 6.f, 0.f, rightLeft*(float)knight.width/6.f, (float)knight.height};
      Rectangle destK{knightPos.x, knightPos.y, 4.0f * (float)knight.width/6.0f, 4.0f * (float)knight.height};
      DrawTexturePro(knight, srcK, destK, Vector2{}, 0.f, WHITE);

      EndDrawing();
   }
   UnloadTexture(map);
   
   CloseWindow();

   return 0;
}