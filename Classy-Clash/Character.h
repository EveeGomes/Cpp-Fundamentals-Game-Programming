#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include "BaseCharacter.h"
#include "raylib.h"

class Character : public BaseCharacter {
public:
   Character();
   Character(int winWidth, int winHeight);
   Vector2 getWorldPos() { return m_worldPos; }
   Vector2 getScreenPos() { return m_screenPos; }
   virtual void tick(float deltaTime);
};
#endif // !CHARACTER_H