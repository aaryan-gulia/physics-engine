#include"System.h"
#include <cstdlib>
#include<iostream>
#include <random>
#include <sys/fcntl.h>
#include"raylib.h"

int main(){

  const int screen_width = 800;
  const int screen_height = 450;

  System system = System();
  system.addObject(Vector3D{300.0f,100.0f,0.0f},10.0f);
  InitWindow(screen_width,screen_height ,"Particle Simulation Using Physics Engine" );

  while(!WindowShouldClose()){
    BeginDrawing();

    auto frame_time = GetFrameTime();    
    ClearBackground(WHITE);
    DrawCircle(system.getCenter()[0],system.getCenter()[1] ,system.getRadius(), BLACK );

    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
      system.addObject(Vector3D{GetMousePosition().x,GetMousePosition().y,0.0f},10.0f);
      }
    for (Particle circle: system.getObjects()){
      DrawCircle(circle.position[0], circle.position[1], circle.radius, BLUE);
    }
    
    system.update(frame_time);   
    
    EndDrawing();
  }
}
