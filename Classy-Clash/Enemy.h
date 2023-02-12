#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "BaseCharacter.h"
#include "Character.h"
#include "raylib.h"

class Enemy : public BaseCharacter {
   Character* m_target{};
public:
   Enemy();
   Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture);
   void setTarget(Character* character) { m_target = character; }
   virtual void tick(float deltaTime);
};

#endif // !ENEMY_H