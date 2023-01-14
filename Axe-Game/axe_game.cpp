#include "raylib.h"

int main() {

   // window dimensions
   int width = 800;
   int height = 450;
   InitWindow(width, height, "Eveline's Window");

   // circle coordinates
   int circle_x = 200; //width / 2;
   int circle_y = 200; //height / 2;
   float circle_radius = 25;
   // circle edges
   int l_circle_x = circle_x - circle_radius;
   int r_circle_x = circle_x + circle_radius;
   int u_circle_y = circle_y - circle_radius;
   int b_circle_y = circle_y + circle_radius;

   // axe coordinates
   int axe_x{ 400 };
   int axe_y{ 0 };
   int axe_height{ 50 };
   int axe_width{ 50 }; // length
   // axe edges
   int l_axe_x = axe_x; // because axe_x is the upper left corner
   int r_axe_x = axe_x + axe_width;
   int u_axe_y = axe_y; // axe_y is the upper left corner as well
   int b_axe_y = axe_y + axe_height;

   int direction{ 7 };

   bool collision_with_axe = ((b_axe_y >= u_circle_y) && 
                              (u_axe_y <= b_circle_y) && 
                              (l_axe_x <= r_circle_x) && 
                              (r_axe_x >= l_circle_x));

   SetTargetFPS(60);
   while (WindowShouldClose() != true) {
      BeginDrawing();
      ClearBackground(BLACK);

      if (collision_with_axe) {
         DrawText("Game Over!", 400, 200, 20, RED);
      }
      else {
         // Game logic begins //

         // update the edges
         l_circle_x = circle_x - circle_radius;
         r_circle_x = circle_x + circle_radius;
         u_circle_y = circle_y - circle_radius;
         b_circle_y = circle_y + circle_radius;

         l_axe_x = axe_x;
         r_axe_x = axe_x + axe_width;
         u_axe_y = axe_y;
         b_axe_y = axe_y + axe_height;

         // update collision_with_axe
         collision_with_axe = ((b_axe_y >= u_circle_y) &&
                               (u_axe_y <= b_circle_y) &&
                               (l_axe_x <= r_circle_x) &&
                               (r_axe_x >= l_circle_x));

         DrawCircle(circle_x, circle_y, circle_radius, BLUE);
         DrawRectangle(axe_x, axe_y, axe_width, axe_height, RED);

         // move the axe
         axe_y += direction;
         if (axe_y > (height - axe_height) || axe_y == 0) {
            direction = -direction; //reverse the direction
         }

         // move the circle
         if (IsKeyDown(KEY_D) && circle_x < width) {
            circle_x += 10;
         }
         if (IsKeyDown(KEY_A) && circle_x > 0) {
            circle_x -= 10;
         }

         if (IsKeyDown(KEY_W)) {
            circle_y -= 10;
         }
         if (IsKeyDown(KEY_S)) {
            circle_y += 10;
         }

         // Game logic ends //
      }

      EndDrawing();
   }
   return 0;
}