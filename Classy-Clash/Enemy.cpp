#include "Enemy.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture) : 
   m_worldPos(pos), 
   m_texture(idle_texture), 
   m_idle(idle_texture), 
   m_run(run_texture) {

   m_width = m_texture.width / m_maxFrames;
   m_height = m_texture.height;
}

void Enemy::tick(float deltaTime) {
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

void Enemy::undoMovement() {
   m_worldPos = m_worldPosLastFrame;
}

Rectangle Enemy::getCollisionRec() {
   return Rectangle{
      m_screenPos.x,
      m_screenPos.y,
      m_width * m_scale,
      m_height * m_scale
   };
}

