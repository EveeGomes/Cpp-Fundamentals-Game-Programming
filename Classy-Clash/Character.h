#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"

class Character {
   Texture2D m_texture{ LoadTexture("characters/knight_idle_spritesheet.png") };
   Texture2D m_idle{ LoadTexture("characters/knight_idle_spritesheet.png") };
   Texture2D m_run{ LoadTexture("characters/knight_run_spritesheet.png") };
   float m_width{};
   float m_height{};

   Vector2 m_screenPos{};
   Vector2 m_worldPos{};

   // animation variables
   float m_rightLeft = 1.f;
   float m_runningTime{};
   int m_frame{};
   int m_maxFrames = 6;
   float m_updateTime = 1.f / 12.f;
   float m_speed = 4.f;

public:
   Character();
   Vector2 getWorldPos() { return m_worldPos; }
   void setScreenPos(int winWidth, int winHeight);
   /*
   *  Tick function takes care of what happens at each and every frame;
   *     It's called every frame (so it's placed inside the Game while loop
   *     We pass dT as a float value, and this value will be used to update all variables on the character that need to be updated.
   */
   void tick(float deltaTime);

};

#endif // !CHARACTER_H