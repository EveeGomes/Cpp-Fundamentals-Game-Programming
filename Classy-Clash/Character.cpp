#include "Character.h"
#include "raymath.h"

Character::Character() {
   m_width = m_texture.width / m_maxFrames;
   m_height = m_texture.height;
}

void Character::setScreenPos(int winWidth, int winHeight) {
   m_screenPos = {
      (float)winWidth / 2.0f - 4.0f * (0.5f * (float)m_texture.width / 6.0f),
      (float)winHeight / 2.0f - 4.0f * (0.5f * (float)m_texture.height)
   };
}

void Character::tick(float deltaTime) {
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
   Rectangle srcK{ m_frame * (float)m_texture.width / 6.f, 0.f, m_rightLeft * (float)m_texture.width / 6.f, (float)m_texture.height };
   Rectangle destK{ m_screenPos.x, m_screenPos.y, 4.0f * (float)m_texture.width / 6.0f, 4.0f * (float)m_texture.height };
   DrawTexturePro(m_texture, srcK, destK, Vector2{}, 0.f, WHITE);
}