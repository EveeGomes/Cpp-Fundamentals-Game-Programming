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

   Vector2 origin{};
   // also, we'll also offset the sword; without it, the weapon would be in a upper position in relation to the character
   //    this offset will be added to the dest Rect in the x and y components
   Vector2 offset{};
   if (m_rightLeft > 0.f) {
      origin = { 0.f, m_weapon.height * m_scale };
      offset = { 38.f, 55.f };
   }
   else {
      origin = { m_weapon.width * m_scale, m_weapon.height * m_scale };
      offset = { 25.f, 55.f };
   }

   // draw the sword
   Rectangle source{ 0.f, 0.f, static_cast<float>(m_weapon.width) * m_rightLeft, static_cast<float>(m_weapon.height) };
   Rectangle dest{ getScreenPos().x + offset.x, getScreenPos().y + offset.y, m_weapon.width * m_scale, m_weapon.height * m_scale };
   DrawTexturePro(m_weapon, source, dest, origin, 0.f, WHITE);

   /**
   * origin vector in DrawTexturePro:
   *  bottom left of weapon texture when character texture is facing right (m_rightLeft > 0.f)
   *  bottom right of weapon texture when character texture is facing left
   * These positions are important for the rotation to give the impression of swinging the sword
   */
   
}