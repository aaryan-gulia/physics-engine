#include "PhysicsWorld.h"

int main(){
  PhysicsWorld system = PhysicsWorld();

  for (uint32_t i = 0; i < 1000; ++i){
    system.update(0.0f);
  }
  
}
