#include"PhysicsWorld.h"
#include <memory>
#include <sys/fcntl.h>
#include"raylib.h"
#include<iostream>

extern const float PARTICLE_RADIUS;
extern const float WINDOW_HEIGHT;
extern const float WINDOW_WIDTH;

PhysicsWorld setup();
std::shared_ptr<Particle> addParticle(float x, float y, PhysicsWorld & world);
std::vector<std::shared_ptr<Particle>> addParticleChain(float x_begin, float y_begin, float x_end, float y_end, 
                                                        PhysicsWorld & world);


int main(){

  PhysicsWorld world = setup();
  addParticle(200.0f, 200.0f, world);
  
  InitWindow(WINDOW_WIDTH,WINDOW_HEIGHT ,"Particle Simulation Using Physics Engine" );

  physics_type::Vector2 starting_pos, ending_pos;
  
  while(!WindowShouldClose()){
    BeginDrawing();

    auto frame_time = GetFrameTime();    
    ClearBackground(LIGHTGRAY);
    DrawFPS(10, 10);
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
      starting_pos = {GetMousePosition().x, GetMousePosition().y};
    }
    if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
      ending_pos = {GetMousePosition().x, GetMousePosition().y};
      addParticleChain(starting_pos.x,starting_pos.y ,ending_pos.x ,ending_pos.y ,world );
      std::cout<<"PARTICLE CHAIN ADDED"<<std::endl;
    }

    for (auto entity: world.getEntities()){
      auto circle = std::dynamic_pointer_cast<Particle>(entity);
      DrawCircle(circle->position.x, circle->position.y, circle->radius, BLUE);
    }

    world.update(frame_time);   
    
    EndDrawing();
  }
}
