#include "Prop.h"
#include "raymath.h"

Prop::Prop() {}

Prop::Prop(Texture2D tex, Vector2 pos) : m_texture(tex), m_worldPos(pos) {}

void Prop::Render(Vector2 knightPos) {
   Vector2 m_screenPos = Vector2Subtract(m_worldPos, knightPos);
   DrawTextureEx(m_texture, m_screenPos, 0.f, m_scale, WHITE);
}
