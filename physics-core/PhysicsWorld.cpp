#include"PhysicsWorld.h"
#include "Entity.h"
#include <chrono>
#include <cstdint>
#include <iostream>
#include <memory>

void PhysicsWorld::update(float _frame_time=0.0f){
  accumulateForces();
  varlet();
  for(uint32_t i = 0; i <= sub_steps; ++i){
    satisfyConstraints();
  }
}

void PhysicsWorld::varlet(){
  auto curr_time = std::chrono::high_resolution_clock::now();
  std::chrono::duration<float> dt = curr_time - last_varlet_time;
  for(uint32_t i = 0; i <= uint32_t(dt.count() / 0.02f); i++){
    es.varletStep(0.01f);
  }
  last_varlet_time = curr_time;
  es.clearForces();
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

EntityStore& PhysicsWorld::getEs(){
  return this->es;
}


uint32_t PhysicsWorld::addParticleEntity(float radius, float mass, float x_position, float y_position, float restitution){
  es.addParticleEntity(radius, mass, {x_position,y_position});
  return es.positions.size()-1;
}

void PhysicsWorld::removeEntity(uint32_t index){
  es.removeParticleEntity(index);
}

void PhysicsWorld::addForceToEntity(uint32_t index, float x_force, float y_force){
  es.applyForce(index,{x_force, y_force});
}

void PhysicsWorld::addConstraint(std::shared_ptr<Constraint> constraint){
  constraints.push_back(constraint);
}

void PhysicsWorld::accumulateForces(){
  for(uint32_t i = 0; i < es.forces.size(); i++){
    es.applyForce(i, {gravity.x, gravity.y});
  }
}


