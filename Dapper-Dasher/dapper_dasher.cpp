#include "raylib.h"

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
   Rectangle nebRec{0.0, 0.0, nebula.width/8, nebula.height/8}; // it can be initialized like that using {} and commas, passing the values in the correct order
   Vector2 nebPos{ windowWidth , windowHeight - nebRec.height };
   
   // nebula X velocity in (pixels/s) so we can use delta time to have this as frame independet
   int nebVel = -200;

   // nebula animation variables
   int nebFrame{};
   const float nebUpdateTime = 1.0 / 12.0;
   float nebRunningTime{};

   // scarfy variables
   Texture2D scarfy = LoadTexture("textures/scarfy.png");
   Rectangle scarfyRec{};
   scarfyRec.width = scarfy.width/6;
   scarfyRec.height = scarfy.height;
   scarfyRec.x = 0;
   scarfyRec.y = 0;
   Vector2 scarfyPos;
   scarfyPos.x = windowWidth / 2 - scarfyRec.width / 2;
   scarfyPos.y = windowHeight - scarfyRec.height;

   // animation frame
   int frame{};
   // amount of time before we update the animation frame
   const float updateTime = 1.0 / 12.0; // 1 12th of a second
   float runningTime{};

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
      nebPos.x += nebVel * dT;

      // update nebula's animation frame
      // update nebula running time
      nebRunningTime += dT;
      if (nebRunningTime >= nebUpdateTime) {
         nebRunningTime = 0.0;
         nebRec.x = nebFrame * nebRec.width;
         nebFrame++;
         if (nebFrame > 7) {
            nebFrame = 0;
         }
      }

      // update scarfy's y position
      scarfyPos.y += velocity * dT;
      
      // update scarfy's animation frame
      if (!isInAir) {
         // update runningTime
         runningTime += dT;
         if (runningTime >= updateTime) { // && !isInAir)
            // update animation frame
            runningTime = 0.0;
            scarfyRec.x = frame * scarfyRec.width;
            frame++;
            // reset the frame when it reaches the last frame
            if (frame > 5) {
               frame = 0;
            }
         }
      }

      // draw the scarfy
      DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);
      
      // draw nebula
      DrawTextureRec(nebula, nebRec, nebPos, WHITE);

      EndDrawing();
   }
   // unload the texture
   UnloadTexture(scarfy);
   UnloadTexture(nebula);

   // raylib function to close the window properly
   CloseWindow();
}