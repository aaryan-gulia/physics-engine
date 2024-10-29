#include"PhysicsWorld.h"
#include <memory>
#include <sys/fcntl.h>
#include"raylib.h"
#include<iostream>
int main(){

  const int screen_width = 800;
  const int screen_height = 450;

  PhysicsWorld system = PhysicsWorld();
  Particle particle(10.0f, 1.0f, {200.0f,200.0f});
  GlobalConstraint globalConstraint(system.getEntities(),{800.0f, 450.0f});
  system.addEntity(std::make_shared<Particle>(particle));
  system.addConstraint(std::make_shared<GlobalConstraint>(globalConstraint));
  
  InitWindow(screen_width,screen_height ,"Particle Simulation Using Physics Engine" );

  while(!WindowShouldClose()){
    BeginDrawing();

    auto frame_time = GetFrameTime();    
    ClearBackground(LIGHTGRAY);
    DrawFPS(10, 10);
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        Particle particle1(10.0f, 1.0f, {GetMousePosition().x,GetMousePosition().y});
        Particle particle2(10.0f, 1.0f, {GetMousePosition().x+20.0f,GetMousePosition().y});
        auto ptr1 = std::make_shared<Particle>(particle1);
        auto ptr2 = std::make_shared<Particle>(particle2);
        // Particle particle3(10.0f, 1.0f, {GetMousePosition().x+40.0f,GetMousePosition().y});
        // Particle particle4(10.0f, 1.0f, {GetMousePosition().x+60.0f,GetMousePosition().y});
        // Particle particle5(10.0f, 1.0f, {GetMousePosition().x+80.0f,GetMousePosition().y});
        // Particle particle6(10.0f, 1.0f, {GetMousePosition().x+100.0f,GetMousePosition().y});
        // Particle particle7(10.0f, 1.0f, {GetMousePosition().x+120.0f,GetMousePosition().y});
        // Particle particle8(10.0f, 1.0f, {GetMousePosition().x+140.0f,GetMousePosition().y});
        RelativeConstraint rl(ptr1,ptr2,0.0f,20.0f);
        system.addEntity(ptr1);
        system.addEntity(ptr2);
        system.addConstraint(std::make_shared<RelativeConstraint>(rl));
      }

    for (auto entity: system.getEntities()){
      auto circle = std::dynamic_pointer_cast<Particle>(entity);
      DrawCircle(circle->position.x, circle->position.y, circle->radius, BLUE);
    }

    system.update(frame_time);   
    
    EndDrawing();
  }
}
