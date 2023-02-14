#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy() {}

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture) {
   m_worldPos = pos;
   m_texture = idle_texture;
   m_idle = idle_texture;
   m_run = run_texture;
   m_width = m_texture.width / m_maxFrames;
   m_height = m_texture.height;
   m_speed = 3.5f;
}


Vector2 Enemy::getScreenPos() const {
   return Vector2Subtract(m_worldPos, m_target->getWorldPos());
}

void Enemy::tick(float deltaTime) {
   if (!getAlive()) return;
   // get to target
   m_velocity = Vector2Subtract(m_target->getScreenPos(), getScreenPos());
   if (Vector2Length(m_velocity) < m_radius) m_velocity = {}; 
   BaseCharacter::tick(deltaTime);
   
   if (CheckCollisionRecs(m_target->getCollisionRec(), getCollisionRec())) {
      m_target->takeDamage(m_damagePerSec * deltaTime);
   }
}