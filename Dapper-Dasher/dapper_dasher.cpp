#include "raylib.h"

struct AnimData {
   Rectangle rec{};
   Vector2 pos{};
   int frame{};
   float updateTime{};
   float runningTime{};
};

bool isOnGround(AnimData data, int windowHeight) {
   return data.pos.y >= windowHeight - data.rec.height;
}

AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame) {
   // update running time
   data.runningTime += deltaTime;
   if (data.runningTime >= data.updateTime) {
      data.runningTime = 0.0;
      // update animation frame
      data.rec.x = data.frame * data.rec.width;
      data.frame++;
      if (data.frame > maxFrame) {
         data.frame = 0;
      }
   }
   return data;
}

int main() {
   // array with window dimensions
   int windowDimensions[2]{};
   windowDimensions[0] = 512; // width
   windowDimensions[1] = 380; // height

   // initialize the window
   InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher Game");

   // acceleration due to gravity (pixels/s)/s
   const int gravity = 1'000;

   // nebula variables
   Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

   const int sizeOfNebulae = 5;
   AnimData nebulae[sizeOfNebulae]{};

   // create a for loop to initialize the nebulas in nebulae array
   for (int i = 0; i < sizeOfNebulae; i++) {
      // select a sprite from the sprite sheet using a rec
      nebulae[i].rec.x = 0.0;
      nebulae[i].rec.y = 0.0;
      nebulae[i].rec.width = nebula.width / 8;
      nebulae[i].rec.height = nebula.height / 8;
      // position in relation to the window (screen)
      nebulae[i].pos.x = windowDimensions[0] + i * 400;
      nebulae[i].pos.y = windowDimensions[1] - nebula.height / 8;
      // variables related to animation
      nebulae[i].frame = 0;
      nebulae[i].runningTime = 0.0;
      nebulae[i].updateTime = 0.0;
   }

   // representation of x pos of a finish line so we can later check each frame and see if scarfy has reached/pass this to win the game
   float finishLine = nebulae[sizeOfNebulae - 1].pos.x;

   int nebVel = -200; // in (pixels/s)

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

   Texture2D background = LoadTexture("textures/far-buildings.png");
   float bgX{};

   Texture2D midground = LoadTexture("textures/back-buildings.png");
   float mgX{};

   Texture2D foreground = LoadTexture("textures/foreground.png");
   float fgX{};

   bool collision{};

   // text for winning or losing the game
   const char* msg = nullptr;
   int textWidth{};

   // set FPS to 60
   SetTargetFPS(60);

   // Game while loop
   while (!WindowShouldClose()) {  
      // delta time (time since last frame)
      const float dT = GetFrameTime();

      BeginDrawing();
      ClearBackground(WHITE);

      // update bgX position to scroll the background
      bgX -= 20 * dT;
      if (bgX <= -background.width * 2) {
         bgX = 0.0;
      }
      // scroll the midground
      mgX -= 40 * dT;
      if (mgX <= -midground.width * 2) {
         mgX = 0.0;
      }
      // scroll the foreground
      fgX -= 80 * dT;
      if (fgX <= -foreground.width * 2) {
         fgX = 0.0;
      }

      // draw the background (right after clearing the background white)
      Vector2 bg1Pos{bgX, 0.0 };
      DrawTextureEx(background, bg1Pos, 0.0, 2.0, WHITE);
      Vector2 bg2Pos{ bgX + background.width * 2, 0.0 };
      DrawTextureEx(background, bg2Pos, 0.0, 2.0, WHITE);

      Vector2 mg1Pos{ mgX, 0.0 };
      DrawTextureEx(midground, mg1Pos, 0.0, 2.0, WHITE);
      Vector2 mg2Pos{ mgX + midground.width * 2, 0.0 };
      DrawTextureEx(midground, mg2Pos, 0.0, 2.0, WHITE);

      Vector2 fg1Pos{ fgX, 0.0 };
      DrawTextureEx(foreground, fg1Pos, 0.0, 2.0, WHITE);
      Vector2 fg2Pos{ fgX + foreground.width * 2, 0.0 };
      DrawTextureEx(foreground, fg2Pos, 0.0, 2.0, WHITE);

      // perform ground check
      if (isOnGround(scarfyData, windowDimensions[1])) {
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
         scarfyData = updateAnimData(scarfyData, dT, 5);
      }

      // update nebulae x positions
      for (int i = 0; i < sizeOfNebulae; i++) {
         nebulae[i].pos.x += nebVel * dT;
      }

      // update nebulae animation frames
      for (int i = 0; i < sizeOfNebulae; i++) {
         nebulae[i] = updateAnimData(nebulae[i], dT, 7);
      }

      // update finishLine, which will have the same velocity as the nebulae
      finishLine += nebVel * dT;

      for (const AnimData& nebula : nebulae) {
         float pad = 50;

         Rectangle nebRec{
            nebula.pos.x + pad,
            nebula.pos.y + pad,
            nebula.rec.width - 2*pad,
            nebula.rec.height - 2*pad
         };
         Rectangle scarfyRec{
            scarfyData.pos.x,
            scarfyData.pos.y,
            scarfyData.rec.width,
            scarfyData.rec.height
         };

         if (CheckCollisionRecs(nebRec, scarfyRec)) {
            collision = true;
         }
      }

      if (collision) {
         // lose the game
         msg = "Game Over!";
         textWidth = MeasureText(msg, 60);
         DrawText(msg, windowDimensions[0]/2 - textWidth/2, windowDimensions[1]/2, 60, RED);
      }
      else if (scarfyData.pos.x >= finishLine) {
         // win the game
         msg = "You Win!";
         textWidth = MeasureText(msg, 60);
         DrawText(msg, windowDimensions[0] / 2 - textWidth / 2, windowDimensions[1] / 2, 60, YELLOW);
      }
      else {
         // draw textures
         // draw scarfy
         DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
         // draw nebulae
         for (int i = 0; i < sizeOfNebulae; i++) {
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
         }
      }
      EndDrawing();
   }
   UnloadTexture(scarfy);
   UnloadTexture(nebula);
   UnloadTexture(background);
   UnloadTexture(midground);
   UnloadTexture(foreground);

   CloseWindow();
}