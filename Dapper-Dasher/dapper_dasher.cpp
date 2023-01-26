#include "raylib.h"

int main() {

   // window dimensions - make them constant
   const int windowWidth = 512;
   const int windowHeight = 380;
   // initialize the window
   InitWindow(windowWidth, windowHeight, "Dapper Dasher Game");

   // acceleration due to gravity (pixels/frame) / frame
   const int gravity = 1;

   // rectangle dimensions
   const int recWidth = 50;
   const int recHeight = 80;
   int posY = windowHeight - recHeight; // To have it positioned on the ground: bottom of the window = windowHeight - recHeight (bcz rectangles use the upper left corner for the coordinates)
   int velocity = 0;

   // set FPS to 60
   SetTargetFPS(10);

   // Game while loop
   while (!WindowShouldClose()) {
            
      BeginDrawing();
      ClearBackground(WHITE);

      // update the velocity by adding the acceleration due to gravity to it: velocity += gravity
      // after that, update the y position!
      // so:
      
      // apply gravity, but before, add a ground check!
      if (posY >= windowHeight - recHeight) {
         // rectangle is on the ground; so we reset the velocity to 0
         velocity = 0;
      }
      else {
         // rectangle is in the air! So we need to apply gravity!
         velocity += gravity;
      }

      // implement JUMP action
      if (IsKeyPressed(KEY_SPACE)) {
         velocity -= 10;
      }

      // update y position
      posY += velocity;

      // now, draw the rectangle
      DrawRectangle(windowWidth / 2, posY, recWidth, recHeight, BLUE);
      
    
      EndDrawing();
   }
   // raylib function to close the window properly
   CloseWindow();
}