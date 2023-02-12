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
   // 1. get toTarget vector value
   Vector2 toTarget = Vector2Subtract(m_target->getScreenPos(), m_screenPos);
   // 2. normalize toTarget
   toTarget = Vector2Normalize(toTarget);
   // 3. multiply toTarget by speed
   toTarget = Vector2Scale(toTarget, m_speed);
   // 4. move Enemy by ADDing m_worldPos and toTarget
   m_worldPos = Vector2Add(m_worldPos, toTarget);

   // set m_screenPos before calling tick function because m_screenPos is used/updated there to draw the enemy to the screen
   m_screenPos = Vector2Subtract(m_worldPos, m_target->getWorldPos());
      
   BaseCharacter::tick(deltaTime);
}