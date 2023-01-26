#include "raylib.h"

int main() {

   // window dimensions - make them constant
   const int windowWidth = 512;
   const int windowHeight = 380;
   // initialize the window
   InitWindow(windowWidth, windowHeight, "Dapper Dasher Game");

   // acceleration due to gravity (pixels/frame) / frame
   const int gravity = 1;

   // is the rectangle in the air?
   bool isInAir = false;
   // jump velocity
   const int jumpVel = -22; // negative since negative directions means upwards!

   // rectangle dimensions
   const int recWidth = 50;
   const int recHeight = 80;
   int posY = windowHeight - recHeight; // To have it positioned on the ground: bottom of the window = windowHeight - recHeight (bcz rectangles use the upper left corner for the coordinates)
   int velocity = 0;

   // set FPS to 60
   SetTargetFPS(60);

   // Game while loop
   while (!WindowShouldClose()) {
            
      BeginDrawing();
      ClearBackground(WHITE);

      if (posY >= windowHeight - recHeight) {
         // rectangle is on the ground; so we reset the velocity to 0
         velocity = 0;
         isInAir = false; // is it needed?
      }
      else {
         // rectangle is in the air! So we need to apply gravity!
         velocity += gravity;
         isInAir = true;
      }

      // implement JUMP action
      if (IsKeyPressed(KEY_SPACE) && !isInAir) { // && !isInAir means only to jump if the character is on the ground; this way it prevents air jumping!
         velocity += jumpVel;
         // using a variable jumpVel instead of a hardcoded value is a better practice!
         // also it becomes easier in case we need to change it
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