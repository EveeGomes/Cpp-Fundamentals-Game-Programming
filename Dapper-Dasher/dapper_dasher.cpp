#include "raylib.h"

int main() {

   // window dimensions - make them constant
   const int windowWidth = 512;
   const int windowHeight = 380;
   // initialize the window
   InitWindow(windowWidth, windowHeight, "Dapper Dasher Game");

   // rectangle dimensions
   const int recWidth = 50;
   const int recHeight = 80;
   int posY = windowHeight - recHeight; // To have it positioned on the ground: bottom of the window = windowHeight - recHeight (bcz rectangles use the upper left corner for the coordinates)
   //int velocity = -10; // negative so it moves upwards
   int velocity = 0;

   // set FPS to 60
   SetTargetFPS(60);

   // Game while loop
   while (!WindowShouldClose()) {
            
      BeginDrawing();
      ClearBackground(WHITE);

      // update the rectangle's position:
      //posY += velocity;

      // using the above logic, implement JUMP action
      if (IsKeyPressed(KEY_SPACE)) {
         velocity += -10;
         
      }
      posY += velocity;

      // now, draw the rectangle
      DrawRectangle(windowWidth / 2, posY, recWidth, recHeight, BLUE);
      
      
      EndDrawing();
   }
   // raylib function to close the window properly
   CloseWindow();
}