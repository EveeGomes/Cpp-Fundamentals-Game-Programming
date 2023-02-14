#include "Character.h"
#include "raymath.h"

Character::Character() {}

Character::Character(int winWidth, int winHeight) : 
   m_windowWidth(winWidth), 
   m_windowHeight(winHeight) {

   m_width = m_texture.width / m_maxFrames;
   m_height = m_texture.height;
}

Vector2 Character::getScreenPos() const {
   return Vector2{
      static_cast<float>(m_windowWidth) / 2.0f - m_scale * (0.5f * m_width),
      static_cast<float>(m_windowHeight) / 2.0f - m_scale * (0.5f * m_height)
   };
}

void Character::takeDamage(float damage) {
   m_health -= damage;
   if (m_health <= 0.f) setAlive(false);
}

void Character::tick(float deltaTime) {
   if (!getAlive()) return;

   if (IsKeyDown(KEY_A)) m_velocity.x -= 1.0f;
   if (IsKeyDown(KEY_D)) m_velocity.x += 1.0f;
   if (IsKeyDown(KEY_W)) m_velocity.y -= 1.0f;
   if (IsKeyDown(KEY_S)) m_velocity.y += 1.0f;

   BaseCharacter::tick(deltaTime);

   Vector2 origin{};
   Vector2 offset{};
   float rotation{};
   if (m_rightLeft > 0.f) {
      origin = { 0.f, m_weapon.height * m_scale };
      offset = { 37.f, 54.f };
      
      m_weaponCollisionRec = {
         getScreenPos().x + offset.x,
         getScreenPos().y + offset.y - m_weapon.height * m_scale,
         m_weapon.width * m_scale,
         m_weapon.height * m_scale
      };

      rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? 35.f : 0.f;
   }
   else {
      origin = { m_weapon.width * m_scale, m_weapon.height * m_scale };
      offset = { 26.f, 54.f };      
      
      m_weaponCollisionRec = {
         getScreenPos().x + offset.x,
         getScreenPos().y + offset.y - m_weapon.height * m_scale,
         m_weapon.width * m_scale,
         m_weapon.height * m_scale
      };

      rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? -35.f : 0.f;
   }

   // draw the sword
   Rectangle source{ 0.f, 0.f, static_cast<float>(m_weapon.width) * m_rightLeft, static_cast<float>(m_weapon.height) };
   Rectangle dest{ getScreenPos().x + offset.x, getScreenPos().y + offset.y, m_weapon.width * m_scale, m_weapon.height * m_scale };
   DrawTexturePro(m_weapon, source, dest, origin, rotation, WHITE);
}