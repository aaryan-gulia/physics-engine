#include"PhysicsWorld.h"
#include <cstdint>
#include <memory>
#include <string>
#include <sys/fcntl.h>
#include "Vector.h"
#include"raylib.h"
#include<iostream>

extern const float PARTICLE_RADIUS;
extern const float WINDOW_HEIGHT;
extern const float WINDOW_WIDTH;

void* operator new(size_t size){
    s_AllocationMetrics.TotalAllocated ++;
    return malloc(size);
}
void* operator new[](size_t size){
    s_AllocationMetrics.TotalAllocated ++;
    return malloc(size);
}

void operator delete(void* memory) noexcept{
    s_AllocationMetrics.TotalFreed ++;
    free(memory);
}

void operator delete[](void* memory) noexcept{
    s_AllocationMetrics.TotalFreed ++;
    free(memory);
}

PhysicsWorld setup();
uint32_t addParticle(float x, float y, float radius_scale, PhysicsWorld & world);
std::vector<std::shared_ptr<Particle>> addParticleChain(float x_begin, float y_begin, float x_end, float y_end, 
                                                        PhysicsWorld & world);
void addRigidBody(float x, float y, PhysicsWorld& world);

int main(){

  PhysicsWorld world = setup();
  addParticle(200.0f, 200.0f, 2, world);

  InitWindow(WINDOW_WIDTH,WINDOW_HEIGHT ,"Particle Simulation Using Physics Engine" );

  physics_type::Vector2 starting_pos, ending_pos;

  while(!WindowShouldClose()){
    BeginDrawing();

    auto frame_time = GetFrameTime();
    ClearBackground(BLACK);
    // if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
    //   starting_pos = {GetMousePosition().x, GetMousePosition().y};
    // }
    // if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
    //   ending_pos = {GetMousePosition().x, GetMousePosition().y};
    //   addParticleChain(starting_pos.x,starting_pos.y ,ending_pos.x ,ending_pos.y ,world );
    // }
    if(IsKeyDown(KEY_SPACE)){
      addParticle(GetMousePosition().x, GetMousePosition().y,1, world);
    }
    if(IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)){
      addParticle(GetMousePosition().x,GetMousePosition().y ,1, world);
    }
    if(IsKeyDown(KEY_R)){
      if(world.getEs().positions.size() > 1){
        world.removeEntity(world.getEs().positions.size() - 1);
      }
    }
    if(IsKeyDown(KEY_W)){
      world.addForceToEntity(0, 0.0f, -1500.0f);
    }
    if(IsKeyDown(KEY_S)){
      world.addForceToEntity(0, 0.0f, 500.0f);
    }
    if(IsKeyDown(KEY_D)){
      world.addForceToEntity(0, 500.0f, 0.0f);
    }
    if(IsKeyDown(KEY_A)){
      world.addForceToEntity(0, -500.0f, 0.0f);
    }

    auto& es = world.getEs();
    uint32_t entity_count;
    DrawCircle(es.positions[0].x, es.positions[0].y, es.ps.radius[0], RED);
    for (entity_count =1; entity_count< es.positions.size(); entity_count++){
      DrawCircle(es.positions[entity_count].x, es.positions[entity_count].y, es.ps.radius[entity_count], BLUE);
    }
    DrawText(std::string("Entity Counter: ").append(std::to_string(entity_count)).c_str(), 5.0, 40.0, 20.0, WHITE);
    DrawText(std::string("Memory Usage: ").append(std::to_string(s_AllocationMetrics.CurrentUsage())).c_str(),
             5.0,60.0,20.0, WHITE);
    DrawFPS(5, 10);
    world.update(frame_time);

    EndDrawing();
  }
}
