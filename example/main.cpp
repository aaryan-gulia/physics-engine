#include"physics.h"
#include<iostream>
#include"raylib.h"

int main(){

  const int screen_width = 800;
  const int screen_height = 450;

  InitWindow(screen_width,screen_height ,"Particle Simulation Using Physics Engine" );

  while(!WindowShouldClose()){
    BeginDrawing();
    ClearBackground(WHITE);
    EndDrawing();
  }
}
