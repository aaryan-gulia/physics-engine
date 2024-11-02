#include"PhysicsWorld.h"
#include <cstdint>
#include <memory>
#include <string>
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
void addRigidBody(float x, float y, PhysicsWorld& world);


int main(){

  PhysicsWorld world = setup();
  addParticle(200.0f, 200.0f, world);
  
  InitWindow(WINDOW_WIDTH,WINDOW_HEIGHT ,"Particle Simulation Using Physics Engine" );

  physics_type::Vector2 starting_pos, ending_pos;
  
  while(!WindowShouldClose()){
    BeginDrawing();

    auto frame_time = GetFrameTime();    
    ClearBackground(BLACK);
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
      starting_pos = {GetMousePosition().x, GetMousePosition().y};
    }
    if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
      ending_pos = {GetMousePosition().x, GetMousePosition().y};
      addParticleChain(starting_pos.x,starting_pos.y ,ending_pos.x ,ending_pos.y ,world );
    }
    if(IsKeyDown(KEY_A) && IsKeyDown(KEY_D)){
      addParticle(GetMousePosition().x, GetMousePosition().y, world);
    }
    if(IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)){
      addParticle(GetMousePosition().x,GetMousePosition().y ,world );
    }

    auto es = world.getEs();
    uint32_t entity_count;
    for (entity_count =0; entity_count< es.positions.size(); entity_count++){
      DrawCircle(es.positions[entity_count].x, es.positions[entity_count].y, es.ps.radius[entity_count], BLUE);
    }
    DrawText(std::string("Entity Counter: ").append(std::to_string(entity_count)).c_str(), 5.0, 40.0, 20.0, WHITE);
    DrawFPS(5, 10);
    world.update(frame_time);   
    
    EndDrawing();
  }
}
