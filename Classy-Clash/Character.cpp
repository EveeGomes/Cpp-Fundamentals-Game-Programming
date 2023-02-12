#include "Character.h"
#include "raymath.h"

Character::Character() {}

Character::Character(int winWidth, int winHeight) : 
   m_windowWidth(winWidth), 
   m_windowHeight(winHeight) {

   m_width = m_texture.width / m_maxFrames;
   m_height = m_texture.height;
}

Vector2 Character::getScreenPos() {
   return Vector2{
      static_cast<float>(m_windowWidth) / 2.0f - m_scale * (0.5f * m_width),
      static_cast<float>(m_windowHeight) / 2.0f - m_scale * (0.5f * m_height)
   };
}

void Character::tick(float deltaTime) {
   // update m_velocity
   if (IsKeyDown(KEY_A)) m_velocity.x -= 1.0f;
   if (IsKeyDown(KEY_D)) m_velocity.x += 1.0f;
   if (IsKeyDown(KEY_W)) m_velocity.y -= 1.0f;
   if (IsKeyDown(KEY_S)) m_velocity.y += 1.0f;

   // then call base tick function which will use this updtaded m_velocity value!
   BaseCharacter::tick(deltaTime);
}