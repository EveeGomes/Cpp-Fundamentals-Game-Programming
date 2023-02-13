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
   Vector2 offset{};
   if (m_rightLeft > 0.f) {
      origin = { 0.f, m_weapon.height * m_scale };
      offset = { 38.f, 55.f };
      m_weaponCollisionRec = {
         getScreenPos().x + offset.x,
         getScreenPos().y + offset.y - m_weapon.height * m_scale,
         m_weapon.width * m_scale,
         m_weapon.height * m_scale
      };
   }
   else {
      origin = { m_weapon.width * m_scale, m_weapon.height * m_scale };
      offset = { 25.f, 55.f };
      m_weaponCollisionRec = {
         getScreenPos().x + offset.x - m_weapon.width * m_scale,
         getScreenPos().y + offset.y - m_weapon.height * m_scale,
         m_weapon.width * m_scale,
         m_weapon.height * m_scale
      };
   }

   // draw the sword
   Rectangle source{ 0.f, 0.f, static_cast<float>(m_weapon.width) * m_rightLeft, static_cast<float>(m_weapon.height) };
   Rectangle dest{ getScreenPos().x + offset.x, getScreenPos().y + offset.y, m_weapon.width * m_scale, m_weapon.height * m_scale };
   DrawTexturePro(m_weapon, source, dest, origin, 0.f, WHITE);

   // using the following function, it's possible to see the Rectangle's lines! In this case we're passing the dest Rectangle information
   DrawRectangleLines(
      //getScreenPos().x + offset.x, getScreenPos().y + offset.y, m_weapon.width * m_scale, m_weapon.height * m_scale, RED
      // now instead of the dest Rec, we'll use the m_weaponCollisionRec
      m_weaponCollisionRec.x,
      m_weaponCollisionRec.y,
      m_weaponCollisionRec.width,
      m_weaponCollisionRec.height,
      RED
   );
   /**
   * the rectangle is below the sword and that's because we've set it to be in the bottom;
   * so the thing to do now is to move the rectangle up by the height of the texture when the character is facing right, and when facing left we'll also need to move left by the width of the weapon texture
   * 
   * Another rectangle member will be added to this Character class called m_weaponCollisionRec that'll be set in this tick function
   */
   
}