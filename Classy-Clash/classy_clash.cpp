#include "raylib.h"
#include "raymath.h"

class Character {
   Texture2D m_texture{ LoadTexture("characters/knight_idle_spritesheet.png") };
   Texture2D m_idle{ LoadTexture("characters/knight_idle_spritesheet.png") };
   Texture2D m_run{ LoadTexture("characters/knight_run_spritesheet.png") };
   Vector2 m_screenPos;
   Vector2 m_worldPos;

   // animation variables
   float rightLeft = 1.f;
   float runningTime{};
   int frame{};
   const int maxFrames = 6;
   const float updateTime = 1.f / 12.f;
   const float speed = 4.f;

public:
   Vector2 getWorldPos() { return m_worldPos; }
   void setScreenPos(int winWidth, int winHeight);
   /*
   *  Tick function takes care of what happens at each and every frame;
   *     It's called every frame (so it's placed inside the Game while loop
   *     We pass dT as a float value, and this value will be used to update all variables on the character that need to be updated.
   */
   void tick(float deltaTime);

};

void Character::setScreenPos(int winWidth, int winHeight) {
   m_screenPos = {
      (float)winWidth / 2.0f - 4.0f * (0.5f * (float)m_texture.width / 6.0f),
      (float)winHeight / 2.0f - 4.0f * (0.5f * (float)m_texture.height)
   };
}

void Character::tick(float deltaTime) {
   // 1st, take the code for handling inputs from the while loop and paste it here;
   // 2nd, change to the member variables
   // 3rd, add direction instead of subtract to m_worldPos
   // vector and keys to determine the direction among the map
   Vector2 direction{};
   if (IsKeyDown(KEY_A)) direction.x -= 1.0f;
   if (IsKeyDown(KEY_D)) direction.x += 1.0f;
   if (IsKeyDown(KEY_W)) direction.y -= 1.0f;
   if (IsKeyDown(KEY_S)) direction.y += 1.0f;

   // direction vector used to move the map:
   if (Vector2Length(direction) != 0.0f) { // checks if direction magnitude isn't zero
      m_texture = m_run;
      // now we'll set m_worldPos to be the sum of m_worldPos + direction (add direction instead of subtracting because now we're changing the character's world position)
      // set m_worldPos = m_worldPos + direction
      m_worldPos = Vector2Add(m_worldPos, Vector2Scale(Vector2Normalize(direction), speed));      // set the rightLeft variable here:
      direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
   }
   else {
      m_texture = m_idle;
   }
}

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

   // create 2 Texture2D using the idle and running knight spritesheets
   Texture2D knight_idle = LoadTexture("characters/knight_idle_spritesheet.png");
   Texture2D knight_run = LoadTexture("characters/knight_run_spritesheet.png");

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
   int frame{};
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
      if (Vector2Length(direction) != 0.0f) { // checks if direction magnitude isn't zero
         knight = knight_run;
         mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), speed));
         // set the rightLeft variable here:
         direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
      }
      else {
         knight = knight_idle;
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
      Rectangle srcK{ frame * (float)knight.width / 6.f, 0.f, rightLeft*(float)knight.width/6.f, (float)knight.height};
      Rectangle destK{knightPos.x, knightPos.y, 4.0f * (float)knight.width/6.0f, 4.0f * (float)knight.height};
      DrawTexturePro(knight, srcK, destK, Vector2{}, 0.f, WHITE);

      EndDrawing();
   }
   UnloadTexture(map);
   
   CloseWindow();

   return 0;
}