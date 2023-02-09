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

   // used to scale the movement vector!
   float speed = 4.0;

   SetTargetFPS(60);

   // Game while loop
   while (!WindowShouldClose()) {

      BeginDrawing();
      ClearBackground(WHITE);

      // check which keys are being pressed so we can update the movement by updating the direction
      // this is done by creating a vector

      Vector2 direction{};
      if (IsKeyDown(KEY_A)) {
         // move to the left:
         direction.x -= 1.0;
      }
      if (IsKeyDown(KEY_D)) {
         direction.x += 1.0;
      }
      if (IsKeyDown(KEY_W)) {
         direction.y -= 1.0;
      }
      if (IsKeyDown(KEY_S)) {
         direction.y += 1.0;
      }

      // now, we use direction vector to move the map
      // need to check if the direction vector is equal to zero; if it is, we don't need to move anywhere!
      if (Vector2Length(direction) != 0.0) { // this function needs raymath.h to be recognized!
         // need to normalize the vector, otherwise we would be moving faster in diagonal than we would actually be moving just down or up.

         // Vector2Normalize(direction) returns a normalized vector; it gives the direction we want to move, but we actually need to move in the oposite direction, meaning we need:
         // set mapPos = mapPos - direction, but this direction has to be the one returned by the normalize function!
         
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