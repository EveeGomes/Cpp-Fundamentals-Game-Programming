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

void Enemy::tick(float deltaTime) {
   
   m_velocity = Vector2Subtract(m_target->getScreenPos(), getScreenPos());
   // in base's tick() there's already the code to normalize, scale and add m_velocity
   BaseCharacter::tick(deltaTime);
}

Vector2 Enemy::getScreenPos() {
   return Vector2Subtract(m_worldPos, m_target->getWorldPos());
}