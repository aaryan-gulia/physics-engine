#include "EntityStore.h"
#include <algorithm>
#include <cstdint>
#include "Vector.h"
#include "iostream"
#include <cassert>
#include <numeric>
void EntityStore::moveEntity_NonVarlet(uint32_t index, const physics_type::Vector2& move_vector){
  positions[index] += move_vector;
  updateAABB(index);
}
void EntityStore::setParticleEntityPosition(uint32_t index,const physics_type::Vector2& position){
  positions[index] = position;
  aabb_max[index] = {position.x + ps.radius[index], position.y + ps.radius[index]};
  aabb_min[index] = {position.x - ps.radius[index], position.y - ps.radius[index]};
}


void EntityStore::addParticleEntity(float radius, float mass, const physics_type::Vector2& position, float restitution){
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

  entity_types.emplace_back(EntityType::PARTICLE);

  // unused for particle entities
  angle.emplace_back();
  old_angle.emplace_back();
}

void EntityStore::addRectangleEntity(float width, float height, float mass, const physics_type::Vector2& position, float restitution){
  physics_type::Vector2 aabb_max_ = {position.x + width/2.0f, position.y + height/2.0f};
  physics_type::Vector2 aabb_min_ = {position.x - width/2.0f, position.y - height/2.0f};
  positions.emplace_back(position);
  old_positions.emplace_back(position);
  restitutions.emplace_back(restitution);
  masses.emplace_back(mass);
  forces.emplace_back();
  rs.height.emplace_back(height);
  rs.width.emplace_back(width);
  rs.entity_index.emplace_back(positions.size() - 1);
  aabb_max.emplace_back(aabb_max_);
  aabb_min.emplace_back(aabb_min_);
  angle.emplace_back(0.0f);
  old_angle.emplace_back(0.0f);

  entity_types.emplace_back(EntityType::RECTANGLE);
}

void EntityStore::removeEntity(uint32_t idx){
  if(entity_types[idx] == EntityType::PARTICLE){
    removeParticleEntity(idx);
  }
  else if(entity_types[idx] == EntityType::RECTANGLE){
    removeRectangleEntity(idx);
  }
  positions.erase(positions.begin() + idx);
  old_positions.erase(old_positions.begin() + idx);
  masses.erase(masses.begin() + idx);
  forces.erase(forces.begin() + idx);
  restitutions.erase(restitutions.begin() + idx);
  aabb_max.erase(aabb_max.begin() + idx);
  aabb_min.erase(aabb_min.begin() + idx);
  angle.erase(angle.begin() + idx);
  old_angle.erase(old_angle.begin() + idx);
}

void EntityStore::removeParticleEntity(uint32_t idx){
  auto particle_iter = std::find(ps.entity_index.begin(), ps.entity_index.end(), idx);
  if(particle_iter != ps.entity_index.end()){
    uint32_t particle_idx = particle_iter - ps.entity_index.begin();
    ps.entity_index.erase(particle_iter);
    ps.radius.erase(ps.radius.begin() + particle_idx);
  }
}

void EntityStore::removeRectangleEntity(uint32_t idx){
  auto rectangle_iter = std::find(rs.entity_index.begin(), rs.entity_index.end(), idx);
  if(rectangle_iter != rs.entity_index.end()){
    uint32_t rectangle_idx = rectangle_iter - rs.entity_index.begin();
    rs.entity_index.erase(rectangle_iter);
    rs.height.erase(rs.height.begin() + rectangle_idx);
    rs.width.erase(rs.width.begin() + rectangle_idx);
  }
}

void EntityStore::applyForce(uint32_t index, const physics_type::Vector2& force_vector){
  forces[index] += force_vector;
}

void EntityStore::clearForces(){
  for(auto& force: forces){
    force = {0.0f,0.0f};
  }
}

void EntityStore::updateAABB(uint32_t index){
  aabb_max[index].x = positions[index].x + ps.radius[index];
  aabb_max[index].y = positions[index].y + ps.radius[index];
  aabb_min[index].x = positions[index].x - ps.radius[index];
  aabb_min[index].y = positions[index].y - ps.radius[index];
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

