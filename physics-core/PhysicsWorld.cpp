#include"PhysicsWorld.h"
#include <cstdint>
#include <iostream>
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
  es.varletStep(dt);
}

void PhysicsWorld::satisfyConstraints(){
  for(auto & constraint: constraints){
    constraint->apply();
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


