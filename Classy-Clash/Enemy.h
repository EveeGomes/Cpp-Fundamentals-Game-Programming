#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"

class Enemy {
   Texture2D m_texture{ LoadTexture("characters/knight_idle_spritesheet.png") };
   Texture2D m_idle{ LoadTexture("characters/knight_idle_spritesheet.png") };
   Texture2D m_run{ LoadTexture("characters/knight_run_spritesheet.png") };
   float m_width{};
   float m_height{};

   Vector2 m_screenPos{};
   Vector2 m_worldPos{};
   Vector2 m_worldPosLastFrame{}; // this one is set in tick() method before anything else!

   // animation variables
   float m_rightLeft = 1.f;
   float m_runningTime{};
   int m_frame{};
   int m_maxFrames = 6;
   float m_updateTime = 1.f / 12.f;
   float m_speed = 4.f;
   float m_scale = 4.f;

public:
   Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture);
   Vector2 getWorldPos() { return m_worldPos; }
   // Tick function takes care of what happens at each and every frame
   void tick(float deltaTime);
   void undoMovement();
   Rectangle getCollisionRec();
};

#endif // !ENEMY_H