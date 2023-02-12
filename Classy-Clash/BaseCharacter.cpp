#include "BaseCharacter.h"

BaseCharacter::BaseCharacter() {}

void BaseCharacter::undoMovement() {
   m_worldPos = m_worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRec() {
   return Rectangle{
      m_screenPos.x,
      m_screenPos.y,
      m_width * m_scale,
      m_height * m_scale
   };
}