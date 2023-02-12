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
}

void Enemy::tick(float deltaTime) {
   // pseudocode to move the enemy towards the character
   // 1. get toTarget vector value
   //       toTarget = character's screen position vector - enemy's screen position vector
   // 2. normalize toTarget
   //       use Vector2Normalize
   // 3. multiply toTarget by speed
   //       use Vector2Scale passing toTarget and a speed value
   // 4. move Enemy by setting the m_worldPos
   //       update m_worldPos by setting it to the value of toTarget


   // set m_screenPos before calling tick function because m_screenPos is used/updated there to draw the enemy to the screen
   m_screenPos = Vector2Subtract(m_worldPos, m_target->getWorldPos());
      
   BaseCharacter::tick(deltaTime);
}