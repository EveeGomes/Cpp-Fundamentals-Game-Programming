#include "raylib.h"

struct AnimData {
   Rectangle rec{};
   Vector2 pos{};
   int frame{};
   float updateTime{};
   float runningTime{};
};

int main() {

   // array with window dimensions
   int windowDimensions[2]{};
   windowDimensions[0] = 512; // width
   windowDimensions[1] = 380; // height

   // initialize the window
   InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher Game");

   // acceleration due to gravity (pixels/s)/s
   const int gravity = 1'000;

   // variables to pass to the draw texture function -> everytime we load a texture it needs to be unloaded at the end

   // nebula variables
   Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
   AnimData nebulae[3]{};

   // create a for loop to initialize the 2 nebulas in nebulae array
   for (int i = 0; i < 3; i++) {
      nebulae[i].rec.x = 0.0;
      nebulae[i].rec.y = 0.0;
      nebulae[i].rec.width = nebula.width / 8;
      nebulae[i].rec.height = nebula.height / 8;
      nebulae[i].pos.y = windowDimensions[1] - nebula.height / 8;
      nebulae[i].frame = 0;
      nebulae[i].runningTime = 0.0;
      nebulae[i].updateTime = 0.0;
   }

   nebulae[0].pos.x = windowDimensions[0];
   nebulae[1].pos.x = windowDimensions[0] + 300;
   nebulae[2].pos.x = windowDimensions[0] + 600;
   
   // nebula X velocity in (pixels/s) so we can use delta time to have this as frame independet
   int nebVel = -200;

   // scarfy variables
   Texture2D scarfy = LoadTexture("textures/scarfy.png");
   AnimData scarfyData;
   scarfyData.rec.width = scarfy.width / 6;
   scarfyData.rec.height = scarfy.height;
   scarfyData.rec.x = 0;
   scarfyData.rec.y = 0;
   scarfyData.pos.x = windowDimensions[0] / 2 - scarfyData.rec.width / 2;
   scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
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

      if (scarfyData.pos.y >= windowDimensions[1] - scarfyData.rec.height) {
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
      nebulae[0].pos.x += nebVel * dT;

      // update nebula's animation frame
      // update nebula running time
      nebulae[0].runningTime += dT;
      if (nebulae[0].runningTime >= nebulae[0].updateTime) {
         nebulae[0].runningTime = 0.0;
         nebulae[0].rec.x = nebulae[0].frame * nebulae[0].rec.width;
         nebulae[0].frame++;
         if (nebulae[0].frame > 7) {
            nebulae[0].frame = 0;
         }
      }

      // second nebula
      nebulae[1].pos.x += nebVel * dT;

      // update second nebula animation frame
      nebulae[1].runningTime += dT;
      if (nebulae[1].runningTime >= nebulae[1].updateTime) {
         nebulae[1].runningTime = 0.0;
         nebulae[1].rec.x = nebulae[1].frame * nebulae[1].rec.width;
         nebulae[1].frame++;
         if (nebulae[1].frame > 7) {
            nebulae[1].frame = 0;
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
      DrawTextureRec(nebula, nebulae[0].rec, nebulae[0].pos, WHITE);

      // draw second nebula
      DrawTextureRec(nebula, nebulae[1].rec, nebulae[1].pos, RED);

      EndDrawing();
   }
   // unload the texture
   UnloadTexture(scarfy);
   UnloadTexture(nebula);

   // raylib function to close the window properly
   CloseWindow();
}