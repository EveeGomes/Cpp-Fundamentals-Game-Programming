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
   if (IsKeyDown(KEY_A)) m_velocity.x -= 1.0f;
   if (IsKeyDown(KEY_D)) m_velocity.x += 1.0f;
   if (IsKeyDown(KEY_W)) m_velocity.y -= 1.0f;
   if (IsKeyDown(KEY_S)) m_velocity.y += 1.0f;

   BaseCharacter::tick(deltaTime);

   // draw the sword
   Rectangle source{ 0.f, 0.f, static_cast<float>(m_weapon.width) * m_rightLeft, static_cast<float>(m_weapon.height) }; // the width and height coming from Texture2D type are int, that's why we cast them to float so it can be compatible with the type float of width and height of the rectangle!
   Rectangle dest{ getScreenPos().x, getScreenPos().y, m_weapon.width * m_scale, m_weapon.height * m_scale }; // for now we're using getScreePos() // also, since m_scale is a float, multiplying it by the width and height will result in a float. That's why we don't need to cast it
   DrawTexturePro(m_weapon, source, dest, {}, 0.f, WHITE);

   /**
   * With these values, the position of the sword isn't correct: upper left corner of the sword is the same as the upper left corner of the character's texture
   * Also, for testing, we'll turn off the Enemy's behavior for now by commenting out the call for the tick function of the base class in Enemy.cpp. This will prevent not only the Enemy to chase the Character but also to render it on the main function
   */
}