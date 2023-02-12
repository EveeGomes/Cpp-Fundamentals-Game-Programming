#include "Character.h"
#include "raymath.h"

Character::Character() {}

Character::Character(int winWidth, int winHeight) {
   m_width = m_texture.width / m_maxFrames;
   m_height = m_texture.height;
   m_screenPos = {
      static_cast<float>(winWidth) / 2.0f - m_scale * (0.5f * m_width),
      static_cast<float>(winHeight) / 2.0f - m_scale * (0.5f * m_height)
   };
}

void Character::tick(float deltaTime) {
   BaseCharacter::tick(deltaTime);

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
}