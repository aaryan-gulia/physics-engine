#include"Entity.h"
#include "Vector.h"

#include <cstdint>
#include <utility>


 
void Entity::varlet(float dt){

  physics_type::Vector2 temp = position;

  this->position = position * 1.99f - position_old * 0.99f + force/mass * dt * dt;

  this->position_old = temp; 

  auto move = this->position - position_old;
  this->aabb.first += move;
  this->aabb.second += move;
}
void EntityStore::moveEntity_NonVarlet(uint32_t index, physics_type::Vector2 move_vector){
  positions[index] += move_vector;
  aabb_max[index] += move_vector;
  aabb_min[index] += move_vector;
}
void EntityStore::setParticleEntityPosition(uint32_t index, physics_type::Vector2 position){
  positions[index] = position;
  aabb_max[index] = {position.x + ps.radius[index], position.y + ps.radius[index]};
  aabb_min[index] = {position.x - ps.radius[index], position.y - ps.radius[index]};
}


void EntityStore::addParticleEntity(float radius, float mass, physics_type::Vector2 position, float restitution){
  ps.radius.emplace_back(radius);
  positions.emplace_back(position);
  old_positions.emplace_back(position);
  restitutions.emplace_back(restitution);
  masses.emplace_back(mass);
  forces.emplace_back();
  ps.entity_index.emplace_back(positions.size() - 1);
  physics_type::Vector2 aabb_max_{position.x + radius, position.y + radius};
  physics_type::Vector2 aabb_min_{position.x - radius, position.y - radius};
  aabb_max.emplace_back(aabb_max_);
  aabb_min.emplace_back(aabb_min_);
}

void EntityStore::applyForce(uint32_t index, physics_type::Vector2 force_vector){
  forces[index] = std::move(force_vector);
}


void EntityStore::varletStep(float dt){
  for(uint32_t i = 0; i< positions.size(); i++){
    auto temp = positions[i];
    positions[i] = positions[i] * 1.99f - old_positions[i] * 0.99f + forces[i] / masses[i] * dt * dt;
    old_positions[i] = temp;
    auto move = positions[i] - old_positions[i];
    aabb_max[i] += move;
    aabb_min[i] += move;
  }
}

