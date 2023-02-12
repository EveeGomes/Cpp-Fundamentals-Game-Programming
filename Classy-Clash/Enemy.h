#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "BaseCharacter.h"
#include "raylib.h"

class Enemy : public BaseCharacter {
public:
   Enemy();
   Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture);
   // Tick function takes care of what happens at each and every frame
   void tick(float deltaTime);
};

#endif // !ENEMY_H