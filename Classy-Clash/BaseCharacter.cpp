#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter() {}

Rectangle BaseCharacter::getCollisionRec() const {
   return Rectangle{
      getScreenPos().x,
      getScreenPos().y,
      m_width * m_scale,
      m_height * m_scale
   };
}

void BaseCharacter::tick(float deltaTime) {
   // first thing to do:
   m_worldPosLastFrame = m_worldPos;

   // update animation frame
   m_runningTime += deltaTime;
   if (m_runningTime >= m_updateTime) {
      m_frame++;
      m_runningTime = 0.f;
      if (m_frame > m_maxFrames) m_frame = 0;
   }

   if (Vector2Length(m_velocity) != 0.0f) {
      m_worldPos = Vector2Add(m_worldPos, Vector2Scale(Vector2Normalize(m_velocity), m_speed));
      m_velocity.x < 0.f ? m_rightLeft = -1.f : m_rightLeft = 1.f;
      m_texture = m_run;
   }
   else {
      m_texture = m_idle;
   }
   m_velocity = {};

   // draw the character
   Rectangle srcK{ m_frame * m_width, 0.f, m_rightLeft * m_width, m_height };
   Rectangle destK{ getScreenPos().x, getScreenPos().y, m_scale * m_width, m_scale * m_height };
   DrawTexturePro(m_texture, srcK, destK, Vector2{}, 0.f, WHITE);
}

void BaseCharacter::undoMovement() {
   m_worldPos = m_worldPosLastFrame;
}