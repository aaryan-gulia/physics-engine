#include"PhysicsWorld.h"
#include <chrono>
#include <cstdint>
#include <iostream>
#include <memory>

void PhysicsWorld::update(float _frame_time=0.0f){
  accumulateForces();
  for(uint32_t i = 0; i <= sub_steps; ++i){
    varlet();
  }
}

void PhysicsWorld::varlet(){
  auto curr_time = std::chrono::high_resolution_clock::now();
  std::chrono::duration<float> dt = curr_time - last_varlet_time;
  for(uint32_t i = 0; i <= uint32_t(dt.count() / 0.02f); i++){
    es.varletStep(0.01f);
    satisfyConstraints();
  }
  last_varlet_time = curr_time;
}

void PhysicsWorld::satisfyConstraints(){
  for(auto & constraint: constraints){
    auto gbc = std::dynamic_pointer_cast<GlobalCollisionConstraint>(constraint);
    if (gbc) {
      gbc ->apply();
    }
    else constraint->apply();
  }
}

std::vector<std::shared_ptr<Entity>>& PhysicsWorld::getEntities(){
  return this->entities;
}

EntityStore& PhysicsWorld::getEs(){
  return this->es;
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
  for(uint32_t i = 0; i < es.forces.size(); i++){
    es.applyForce(i, {gravity.x, gravity.y});
  }
}


