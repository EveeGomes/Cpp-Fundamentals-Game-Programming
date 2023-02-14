#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "BaseCharacter.h"
#include "Character.h"
#include "raylib.h"

class Enemy : public BaseCharacter {
   Character* m_target{};
   float m_damagePerSec = 10.f;
public:
   Enemy();
   Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture);
   
   virtual Vector2 getScreenPos() const;
   
   void setTarget(Character* character) { m_target = character; }
   virtual void tick(float deltaTime);
};

#endif // !ENEMY_H