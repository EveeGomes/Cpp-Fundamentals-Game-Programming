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

   /*Vector2 m_screenPos{};
   * instead of using a variable, there'll be a getter that's pure virtual and can be ovewritten in any derived class using different code for their own purpose.
   * the existence of a pure virtual function makes a class as an abstract one!
   */
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
   // this vector2 will be used for updating both enemy and character's position
   //    it'll contain information regarding the movement direction and the distance each frame should move
   Vector2 m_velocity{};

public:
   BaseCharacter();
   virtual void tick(float deltaTime);
   virtual Vector2 getScreenPos() = 0;
   Vector2 getWorldPos() { return m_worldPos; }
   void undoMovement();
   Rectangle getCollisionRec();
};

#endif // !BASE_CHARACTER_H