#pragma once
#ifndef PROP_H
#define PROP_H

#include "raylib.h"

class Prop {
   Texture2D m_texture{};
   Vector2 m_worldPos{};
   float m_scale = 4.f;

public:
   Prop();
   Prop(Texture2D tex, Vector2 pos);
   void Render(Vector2 knightPos);
   Rectangle getCollisionRec(Vector2 knightPos);
};

#endif // !PROP_H