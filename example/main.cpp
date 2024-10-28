#include"System.h"
#include <cstdlib>
#include<iostream>
#include <random>
#include <sstream>
#include <string>
#include <sys/fcntl.h>
#include"raylib.h"

int main(){

  const int screen_width = 800;
  const int screen_height = 450;

  System system = System();
  system.addObject(physics_type::Vector2{300.0f,100.0f},10.0f);
  InitWindow(screen_width,screen_height ,"Particle Simulation Using Physics Engine" );

  while(!WindowShouldClose()){
    BeginDrawing();

    auto frame_time = GetFrameTime();    
    ClearBackground(LIGHTGRAY);
    DrawCircle(system.getCenter().x,system.getCenter().y ,system.getRadius(), BLACK );
    DrawFPS(10, 10);
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
      system.addObject(physics_type::Vector2{GetMousePosition().x,GetMousePosition().y},10.0f);
      }
    for (Particle circle: system.getObjects()){
      DrawCircle(circle.position.x, circle.position.y, circle.radius, BLUE);
    }
    
    system.update(frame_time);   
    
    EndDrawing();
  }
}
