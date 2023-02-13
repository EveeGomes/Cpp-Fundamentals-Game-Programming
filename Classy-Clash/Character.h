#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include "BaseCharacter.h"
#include "raylib.h"

class Character : public BaseCharacter {
   int m_windowWidth{};
   int m_windowHeight{};
   Texture2D m_weapon{LoadTexture("characters/weapon_sword.png")};
public:
   Character();
   Character(int winWidth, int winHeight);
   Vector2 getWorldPos() { return m_worldPos; }
   virtual Vector2 getScreenPos();
   virtual void tick(float deltaTime);
};
#endif // !CHARACTER_H