#include"physics.h"
#include<iostream>
#include"raylib.h"

int main(){

  const int screen_width = 800;
  const int screen_height = 450;

  physics2D::System system = physics2D::System(physics2D::Vector(screen_width,screen_height),
                                               physics2D::Vector(0.0,10.0));
  system.addRigidBody2DCircle(20,10 ,physics2D::Vector(200,200),physics2D::Vector(0,0));

  InitWindow(screen_width,screen_height ,"Particle Simulation Using Physics Engine" );
    
  SetTargetFPS(60);
  while(!WindowShouldClose()){
    BeginDrawing();
    
    ClearBackground(WHITE);

    for (physics2D::RigidBody2DCircle circle: system.circles){
      DrawCircle(circle.center.x, circle.center.y, circle.radius, BLACK);
    }
    system.propogate(1.0/60.0);   
    EndDrawing();
  }
}
