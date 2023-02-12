#pragma once
#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H
#include "raylib.h"

class BaseCharacter {
protected:
   /*Texture2D m_texture{};
   Texture2D m_idle{};
   Texture2D m_run{};*/
   Texture2D m_texture{ LoadTexture("characters/knight_idle_spritesheet.png") };
   Texture2D m_idle{ LoadTexture("characters/knight_idle_spritesheet.png") };
   Texture2D m_run{ LoadTexture("characters/knight_run_spritesheet.png") };
   float m_width{};
   float m_height{};

   Vector2 m_screenPos{};
   Vector2 m_worldPos{};
   Vector2 m_worldPosLastFrame{};

   // animation variables
   float m_rightLeft = 1.f;
   float m_runningTime{};
   int m_frame{};
   int m_maxFrames = 6;
   float m_updateTime = 1.f / 12.f;
   float m_speed = 4.f;
   float m_scale = 4.f;

public:
   BaseCharacter();

   Vector2 getWorldPos() { return m_worldPos; }
   void undoMovement();
   Rectangle getCollisionRec();
};

#endif // !BASE_CHARACTER_H