#include "raylib.h"

struct AnimData {
   Rectangle rec{};
   Vector2 pos{};
   int frame{};
   float updateTime{};
   float runningTime{};
};

int main() {

   // window dimensions - make them constant
   const int windowWidth = 512;
   const int windowHeight = 380;
   // initialize the window
   InitWindow(windowWidth, windowHeight, "Dapper Dasher Game");

   // acceleration due to gravity (pixels/s)/s
   const int gravity = 1'000;

   // variables to pass to the draw texture function -> everytime we load a texture it needs to be unloaded at the end

   // nebula variables
   Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
   // AnimData object for nebula
   AnimData nebData{
      {0.0, 0.0, nebula.width / 8, nebula.height / 8},   // Rectangle rec
      {windowWidth , windowHeight - nebula.height / 8},  // Vector2 pos
      0,                                                 // int frame
      1.0 / 12.0,                                        // float updateTime
      0.0                                                // float runningTime
   };

   // AnimData instance for the second nebula
   AnimData neb2Data{
      {0.0, 0.0, nebula.width / 8, nebula.height / 8},         // Rectangle rec
      {windowWidth + 300, windowHeight - nebula.height / 8},   // Vector2 pos
      0,                                                       // int frame
      1.0/16.0,                                                // float updateTime
      0.0                                                      // float runningTime
   };
   
   // nebula X velocity in (pixels/s) so we can use delta time to have this as frame independet
   int nebVel = -200;

   // scarfy variables
   Texture2D scarfy = LoadTexture("textures/scarfy.png");
   AnimData scarfyData;
   scarfyData.rec.width = scarfy.width / 6;
   scarfyData.rec.height = scarfy.height;
   scarfyData.rec.x = 0;
   scarfyData.rec.y = 0;
   scarfyData.pos.x = windowWidth / 2 - scarfyData.rec.width / 2;
   scarfyData.pos.y = windowHeight - scarfyData.rec.height;
   scarfyData.frame = 0;
   scarfyData.updateTime = 1.0 / 12.0;
   scarfyData.runningTime = 0.0;

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

      if (scarfyData.pos.y >= windowHeight - scarfyData.rec.height) {
         velocity = 0;
         isInAir = false;
      }
      else {
         velocity += gravity * dT;
         isInAir = true;
      }

      // implement JUMP action
      if (IsKeyPressed(KEY_SPACE) && !isInAir) {
         velocity += jumpVel;
      }

      // update nebula's x position
      nebData.pos.x += nebVel * dT;

      // update nebula's animation frame
      // update nebula running time
      nebData.runningTime += dT;
      if (nebData.runningTime >= nebData.updateTime) {
         nebData.runningTime = 0.0;
         nebData.rec.x = nebData.frame * nebData.rec.width;
         nebData.frame++;
         if (nebData.frame > 7) {
            nebData.frame = 0;
         }
      }

      // second nebula
      neb2Data.pos.x += nebVel * dT;

      // update second nebula animation frame
      neb2Data.runningTime += dT;
      if (neb2Data.runningTime >= neb2Data.updateTime) {
         neb2Data.runningTime = 0.0;
         neb2Data.rec.x = neb2Data.frame * neb2Data.rec.width;
         neb2Data.frame++;
         if (neb2Data.frame > 7) {
            neb2Data.frame = 0;
         }
      }


      // update scarfy's y position
      scarfyData.pos.y += velocity * dT;
      
      // update scarfy's animation frame
      if (!isInAir) {
         // update runningTime
         scarfyData.runningTime += dT;
         if (scarfyData.runningTime >= scarfyData.updateTime) {
            // update animation frame
            scarfyData.runningTime = 0.0;
            scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
            scarfyData.frame++;
            // reset the frame when it reaches the last frame
            if (scarfyData.frame > 5) {
               scarfyData.frame = 0;
            }
         }
      }

      // draw the scarfy
      DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
      
      // draw nebula
      DrawTextureRec(nebula, nebData.rec, nebData.pos, WHITE);

      // draw second nebula
      DrawTextureRec(nebula, neb2Data.rec, neb2Data.pos, RED);

      EndDrawing();
   }
   // unload the texture
   UnloadTexture(scarfy);
   UnloadTexture(nebula);

   // raylib function to close the window properly
   CloseWindow();
}