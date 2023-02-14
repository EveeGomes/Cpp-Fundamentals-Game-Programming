#pragma once
#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H
#include "raylib.h"

class BaseCharacter {
   bool m_alive = true;
protected:
   /*Texture2D m_texture{};
   Texture2D m_idle{};
   Texture2D m_run{};*/
   Texture2D m_texture{ LoadTexture("characters/knight_idle_spritesheet.png") };
   Texture2D m_idle{ LoadTexture("characters/knight_idle_spritesheet.png") };
   Texture2D m_run{ LoadTexture("characters/knight_run_spritesheet.png") };
   float m_width{};
   float m_height{};

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
   Vector2 m_velocity{};

public:
   BaseCharacter();
   
   virtual Vector2 getScreenPos() const = 0;
   Vector2 getWorldPos() const { return m_worldPos; }
   bool getAlive() const { return m_alive; }
   Rectangle getCollisionRec() const;
   
   void setAlive(bool isAlive) { m_alive = isAlive; }
   virtual void tick(float deltaTime);
   void undoMovement();
   
};

#endif // !BASE_CHARACTER_H