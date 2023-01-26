#include "raylib.h"

int main() {

   // window dimensions - make them constant
   const int windowWidth = 512;
   const int windowHeight = 380;
   // initialize the window
   InitWindow(windowWidth, windowHeight, "Dapper Dasher Game");

   // acceleration due to gravity (pixels/s)/s
   const int gravity = 1'000;

   // variables to pass to the draw texture function
   Texture2D scarfy = LoadTexture("textures/scarfy.png");
   Rectangle scarfyRec;
   scarfyRec.width = scarfy.width/6;
   scarfyRec.height = scarfy.height;
   scarfyRec.x = 0;
   scarfyRec.y = 0;

   Vector2 scarfyPos;
   scarfyPos.x = windowWidth / 2 - scarfyRec.width / 2;
   scarfyPos.y = windowHeight - scarfyRec.height;

   bool isInAir = false;
   // jump velocity
   const int jumpVel = -600; // pixels/s 

   int velocity = 0;

   // set FPS to 60
   SetTargetFPS(60);

   // Game while loop
   while (!WindowShouldClose()) {  
      BeginDrawing();
      ClearBackground(WHITE);

      // delta time (time since last frame)
      const float dT = GetFrameTime();

      if (scarfyPos.y >= windowHeight - scarfyRec.height) {
         velocity = 0;
         isInAir = false; // is it needed? -> yes! otherwise it'll keep the value of the else block and won't jump! :)
      }
      else {
         // multiply by dT when applying gravity
         velocity += gravity * dT;
         isInAir = true;
      }

      // implement JUMP action
      if (IsKeyPressed(KEY_SPACE) && !isInAir) {
         velocity += jumpVel;
      }

      // update y position
      scarfyPos.y += velocity * dT; // multiply by dT when applying velocity
      
      // Draw the character
      DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);
      
      EndDrawing();
   }
   // unload the texture
   UnloadTexture(scarfy);

   // raylib function to close the window properly
   CloseWindow();
}