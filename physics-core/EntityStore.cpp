#include "EntityStore.h"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include "Entity.h"
#include "Vector.h"
#include "iostream"
#include <cassert>
#include <memory>
#include <numeric>

using namespace physics_entity;

void EntityStore::moveEntity_NonVarlet(uint32_t index, const physics_type::Vector2& move_vector){
  positions[index] += move_vector;
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
  aabb_max.emplace_back(position.x + radius, position.y + radius);
  aabb_min.emplace_back(position.x - radius, position.y - radius);

  entity_types.emplace_back(EntityType::PARTICLE);

  // unused for particle entities
  angle.emplace_back();
  old_angle.emplace_back();
  torques.emplace_back();
  moment_of_inertia.emplace_back();
}

void EntityStore::addRectangleEntity(float width, float height, float mass, const physics_type::Vector2& position, float restitution){
  entity_types.emplace_back(EntityType::RECTANGLE);
  positions.emplace_back(position);
  old_positions.emplace_back(position);
  restitutions.emplace_back(restitution);
  masses.emplace_back(mass);
  forces.emplace_back();
  rs.height.emplace_back(height);
  rs.width.emplace_back(width);
  rs.entity_index.emplace_back(positions.size() - 1);
  aabb_max.emplace_back(position.x + width/2.0f, position.y + height/2.0f);
  aabb_min.emplace_back(position.x - width/2.0f, position.y - height/2.0f);

  angle.emplace_back(0.0f);
  old_angle.emplace_back(0.0f);
  torques.emplace_back();
  moment_of_inertia.emplace_back(mass * (width * width + height * height) / 12.0f);
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
  torques.erase(torques.begin() + idx);
  moment_of_inertia.erase(moment_of_inertia.begin() + idx);
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

void EntityStore::updateParticleAABB(uint32_t index){
  auto particle_idx = getParticleStoreIdx(index);
  aabb_max[index].x = positions[index].x + ps.radius[particle_idx];
  aabb_max[index].y = positions[index].y + ps.radius[particle_idx];
  aabb_min[index].x = positions[index].x - ps.radius[particle_idx];
  aabb_min[index].y = positions[index].y - ps.radius[particle_idx];
}

void EntityStore::updateRectangleAABB(uint32_t index){
  auto rect_idx = getRectangleStoreIdx(index);
  float a = angle[index];
  float aabb_height = rs.height[rect_idx] * std::cos(a) + rs.width[rect_idx] * std::sin(a);
  float aabb_width = rs.height[rect_idx] * std::sin(a) + rs.width[rect_idx] * std::cos(a);
  
  aabb_max[index].x = positions[index].x + aabb_width / 2.0f;
  aabb_max[index].y = positions[index].y + aabb_height / 2.0f;
  aabb_min[index].x = positions[index].x - aabb_width / 2.0f;
  aabb_min[index].y = positions[index].y - aabb_height / 2.0f;
}

void EntityStore::varletStep(float dt, float dampening_coef){
  for(uint32_t i = 0; i< positions.size(); i++){
    // TODO: NEED TO IMPLEMENT TIME INVARIANT VERSION OF VERLET INTEGRATOR
    // position verlet 
    auto temp = positions[i];
    positions[i] = positions[i] * (2.0f - dampening_coef) - old_positions[i] * (1.0f - dampening_coef) 
                   + forces[i] / masses[i] * dt * dt;
    old_positions[i] = temp;

    // angle verlet
    auto temp_angle = angle[i];
    angle[i] = angle[i] * (2.0f - dampening_coef) - old_angle[i] * (1.0f - dampening_coef) 
               + torques[i] / moment_of_inertia[i] * dt * dt;
  }

  for(uint32_t i = 0; i < positions.size(); i++){
    if(entity_types[i] == PARTICLE){
      updateParticleAABB(i);
    }
    else if(entity_types[i] == RECTANGLE){
      updateRectangleAABB(i);
    }
  }
}

std::unique_ptr<Entity> EntityStore::getEntity(uint32_t idx){
  
  if(entity_types[idx] == PARTICLE){
    auto particle_iter = std::find(ps.entity_index.begin(), ps.entity_index.end(), idx);
    uint32_t particle_idx = particle_iter - ps.entity_index.begin();
    float& radius = ps.radius.at(particle_idx);
    return std::make_unique<Particle>(Particle(positions[idx],angle[idx],forces[idx],masses[idx],restitutions[idx],radius));
  }

  else if(entity_types[idx] == RECTANGLE){
    auto rectangle_iter = std::find(rs.entity_index.begin(), rs.entity_index.end(), idx);
    uint32_t rectangle_idx = rectangle_iter - rs.entity_index.begin();
    float& height = rs.height.at(rectangle_idx);
    float& width = rs.width.at(rectangle_idx);
    return std::make_unique<Rectangle>(Rectangle(positions[idx],angle[idx],forces[idx],masses[idx],restitutions[idx],
                                                height, width));
  }

  else{
    std::cerr << "UNKNOWN ENTITY" ;
    return nullptr;
  }
}

size_t EntityStore::getParticleStoreIdx(uint32_t idx){
  auto particle_ptr = std::find(ps.entity_index.begin(), ps.entity_index.end(), idx);
  if (particle_ptr == ps.entity_index.end()){
    std::cerr << "idx NOT IN PARTICLE STORE";
    return NULL;
  }
  return std::find(ps.entity_index.begin(), ps.entity_index.end(), idx) - ps.entity_index.begin();
}

size_t EntityStore::getRectangleStoreIdx(uint32_t idx){
  auto rectangle_ptr = std::find(rs.entity_index.begin(), rs.entity_index.end(), idx);
  if (rectangle_ptr == rs.entity_index.end()){
    std::cerr << "idx NOT IN RECTANGLE STORE";
    return NULL;
  }
  return std::find(rs.entity_index.begin(), rs.entity_index.end(), idx) - rs.entity_index.begin();
}
