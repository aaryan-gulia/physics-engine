#include"Entity.h"

#include <utility>


 
void Entity::varlet(float dt){

  physics_type::Vector2 temp = position;

  this->position = position * 1.99f - position_old * 0.99f + force/mass * dt * dt;

  this->position_old = temp; 

  auto move = this->position - position_old;
  this->aabb.first += move;
  this->aabb.second += move;
}
void EntityStore::moveEntity_NonVarlet(uint32_t index, Eigen::Vector2f move_vector){
  positions[index] += move_vector;
  aabb_max[index] += move_vector;
  aabb_min[index] += move_vector;
}


void EntityStore::addParticleEntity(float radius, float mass, float position[2], float restitution){
  ps.radius.emplace_back(radius);
  positions.emplace_back(position);
  old_positions.emplace_back(position);
  restitutions.emplace_back(restitution);
  masses.emplace_back(mass);
  forces.emplace_back();
  ps.entity_index.emplace_back(positions.size() - 1);
  float aabb_max_[2] = {position[0] + radius, position[1] + radius};
  float aabb_min_[2] = {position[0] - radius, position[1] - radius};
  aabb_max.emplace_back(aabb_max_);
  aabb_min.emplace_back(aabb_min_);
}

void EntityStore::applyForce(uint32_t index, Eigen::Vector2f force_vector){
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

