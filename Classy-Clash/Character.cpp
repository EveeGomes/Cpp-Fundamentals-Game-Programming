#include "Character.h"
#include "raymath.h"

Character::Character() {}

Character::Character(int winWidth, int winHeight) {
   m_width = m_texture.width / m_maxFrames;
   m_height = m_texture.height;
   m_screenPos = {
      // instead of using a C casting type, which is dangerous as it doesn't check for the type it's casting to/from, here we'll change to a C++ casting function that checks the types at compile time and prevents casting incompatible types!
      static_cast<float>(winWidth) / 2.0f - m_scale * (0.5f * m_width),
      static_cast<float>(winHeight) / 2.0f - m_scale * (0.5f * m_height)
   };
}

void Character::tick(float deltaTime) {
   // first thing to do: set m_worldPosLastFrame to m_worldPos
   m_worldPosLastFrame = m_worldPos;

   // vector and keys to determine the direction among the map
   Vector2 direction{};
   if (IsKeyDown(KEY_A)) direction.x -= 1.0f;
   if (IsKeyDown(KEY_D)) direction.x += 1.0f;
   if (IsKeyDown(KEY_W)) direction.y -= 1.0f;
   if (IsKeyDown(KEY_S)) direction.y += 1.0f;

   // direction vector used to move the map:
   if (Vector2Length(direction) != 0.0f) { // checks if direction magnitude isn't zero
      m_texture = m_run;
      // set m_worldPos = m_worldPos + direction
      m_worldPos = Vector2Add(m_worldPos, Vector2Scale(Vector2Normalize(direction), m_speed));      // set the rightLeft variable here:
      direction.x < 0.f ? m_rightLeft = -1.f : m_rightLeft = 1.f;
   }
   else {
      m_texture = m_idle;
   }

   // add the animation code to tick method
   // update animation frame
   m_runningTime += deltaTime;
   if (m_runningTime >= m_updateTime) {
      m_frame++;
      m_runningTime = 0.f;
      if (m_frame > m_maxFrames) m_frame = 0;
   }

   // draw the character
   Rectangle srcK{ m_frame * m_width, 0.f, m_rightLeft * m_width, m_height };
   Rectangle destK{ m_screenPos.x, m_screenPos.y, m_scale * m_width, m_scale * m_height };
   DrawTexturePro(m_texture, srcK, destK, Vector2{}, 0.f, WHITE);
}

void Character::undoMovement() {
   m_worldPos = m_worldPosLastFrame; 
}

Rectangle Character::getCollisionRec() {
   return Rectangle{
      m_screenPos.x,
      m_screenPos.y,
      m_width * m_scale,
      m_height * m_scale
   };
}
