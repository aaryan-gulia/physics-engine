#include"PhysicsWorld.h"
#include <cstdint>
#include <memory>

void PhysicsWorld::update(float _frame_time=0.0f){
  accumulateForces();
  varlet();
  for(uint32_t i{0}; i < this->sub_steps; ++i){
    satisfyConstraints();
  }
}

void PhysicsWorld::varlet(){
  for(auto& particle: entities){
    particle->varlet(this->dt);
    particle->force = {0.0f,0.0f};
  }
}

void PhysicsWorld::satisfyConstraints(){
  for(auto & constraint: constraints){
    constraint->apply();
  }
}

std::vector<std::shared_ptr<Entity>>& PhysicsWorld::getEntities(){
  return this->entities;
}

void PhysicsWorld::addEntity(std::shared_ptr<Entity> entity){
  entities.push_back(entity);
}
void PhysicsWorld::addConstraint(std::shared_ptr<Constraint> constraint){
  constraints.push_back(constraint);
}

void PhysicsWorld::accumulateForces(){
  for(auto& particle: entities){
    particle->force += this->gravity;    
  }
}


