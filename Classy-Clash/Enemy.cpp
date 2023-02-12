#include "Enemy.h"

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
   // all that's needed here is to call the base class version of tick;
   // **** important **** if we didn't want any extra functionality into this Enemy version of tick, we wouldn't need to override here in this class; it would be used since this is a derived class alread (just like the other functions - getWorldPos() etc)
   BaseCharacter::tick(deltaTime);
}