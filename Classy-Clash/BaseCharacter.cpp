#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter() {}

void BaseCharacter::tick(float deltaTime) {
   // first thing to do: set m_worldPosLastFrame to m_worldPos
   m_worldPosLastFrame = m_worldPos;

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

void BaseCharacter::undoMovement() {
   m_worldPos = m_worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRec() {
   return Rectangle{
      m_screenPos.x,
      m_screenPos.y,
      m_width * m_scale,
      m_height * m_scale
   };
}