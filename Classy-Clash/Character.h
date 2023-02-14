#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include "BaseCharacter.h"
#include "raylib.h"

class Character : public BaseCharacter {
   int m_windowWidth{};
   int m_windowHeight{};
   Texture2D m_weapon{LoadTexture("characters/weapon_sword.png")};
   Rectangle m_weaponCollisionRec{};
   float m_health = 100.f;
public:
   Character();
   Character(int winWidth, int winHeight);

   Vector2 getWorldPos() const { return m_worldPos; }
   virtual Vector2 getScreenPos() const;
   Rectangle getWeaponCollisionRec() const { return m_weaponCollisionRec; }
   float getHealth() const { return m_health; }
   
   virtual void tick(float deltaTime);
};
#endif // !CHARACTER_H