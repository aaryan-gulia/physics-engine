#include"System.h"
#include <cstdlib>
#include<iostream>
#include <random>
#include"raylib.h"

int main(){

  const int screen_width = 800;
  const int screen_height = 450;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distribute(-100,100);

  System system = System();
  system.addObject(Vector3D{300.0f,100.0f,0.0f},20.0 );
  InitWindow(screen_width,screen_height ,"Particle Simulation Using Physics Engine" );
  
  while(!WindowShouldClose()){
    BeginDrawing();
    
    ClearBackground(WHITE);

    for (Particle circle: system.getObjects()){
      DrawCircle(circle.position[0], circle.position[1], circle.radius, BLACK);
    }
    
    system.update();   
    
    EndDrawing();
  }
}
