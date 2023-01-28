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

   const int sizeOfNebulae = 10;
   AnimData nebulae[sizeOfNebulae]{};

   // create a for loop to initialize the 2 nebulas in nebulae array
   for (int i = 0; i < sizeOfNebulae; i++) {
      nebulae[i].rec.x = 0.0;
      nebulae[i].rec.y = 0.0;
      nebulae[i].rec.width = nebula.width / 8;
      nebulae[i].rec.height = nebula.height / 8;
      nebulae[i].pos.x = windowDimensions[0] + i * 300;
      nebulae[i].pos.y = windowDimensions[1] - nebula.height / 8;
      nebulae[i].frame = 0;
      nebulae[i].runningTime = 0.0;
      nebulae[i].updateTime = 0.0;
   }
   
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

      // update nebulae x positions
      for (int i = 0; i < sizeOfNebulae; i++) {
         nebulae[i].pos.x += nebVel * dT;
      }

      // update nebulae animation frames
      for (int i = 0; i < sizeOfNebulae; i++) {
         nebulae[i].runningTime += dT;
         if (nebulae[i].runningTime >= nebulae[i].updateTime) {
            nebulae[i].runningTime = 0.0;
            nebulae[i].rec.x = nebulae[i].frame * nebulae[i].rec.width;
            nebulae[i].frame++;
            if (nebulae[i].frame > 7) {
               nebulae[i].frame = 0;
            }
         }
      }

      // draw scarfy
      DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

      // draw nebulae
      for (int i = 0; i < sizeOfNebulae; i++) {
         DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
      }

      EndDrawing();
   }
   // unload the texture
   UnloadTexture(scarfy);
   UnloadTexture(nebula);

   // raylib function to close the window properly
   CloseWindow();
}