#include"Constraint.h"
#include "Vector.h"
#include <cmath>
#include <cstdint>
#include <iostream>
#include <tuple>
#include <vector>

std::tuple<bool,std::vector<physics_type::Vector2>> GJK_intersection_test(uint32_t id1, uint32_t id2, EntityStore& es);
std::tuple<float, physics_type::Vector2> EPA_collision_details(uint32_t id1, uint32_t id2, const EntityStore& es, std::vector<physics_type::Vector2>& simplex);

void GlobalCollisionConstraint::apply(){
  m_collision_grid.updatedGrid(m_es.aabb_min, m_es.aabb_max);
  auto boundaryEntities = m_collision_grid.getBoundaryIndices();
  
  for(auto entity: boundaryEntities){
    applyGlobalBoundary(entity);
  }

  for(auto grid_cell: m_collision_grid.m_dense_grid){
    auto collisionEntities = grid_cell.second;
    for(uint32_t i = 0; i < collisionEntities.size(); i++){
      for(uint32_t j = i + 1; j < collisionEntities.size(); j++){
       if(aabbOverlapCheck(collisionEntities[i], collisionEntities[j])){
          applyGlobalCollisionResolution(collisionEntities[i],collisionEntities[j]);
       }
      }
    }
  }

}


void GlobalCollisionConstraint::applyGlobalBoundary(uint32_t entity_index){
  if(m_es.aabb_min.at(entity_index).x < 0 ){
    m_es.moveEntity_NonVarlet(entity_index, {-1*m_es.aabb_min.at(entity_index).x, 0.0f});
  }
  if(m_es.aabb_min.at(entity_index).y < 0 ){
    m_es.moveEntity_NonVarlet(entity_index, {0.0f,-1*m_es.aabb_min.at(entity_index).y});
  }
  if(m_es.aabb_max.at(entity_index).x > m_global_boundary.x){
    m_es.moveEntity_NonVarlet(entity_index,{m_global_boundary.x-m_es.aabb_max.at(entity_index).x,0.0f});
  }
  if(m_es.aabb_max.at(entity_index).y > m_global_boundary.y){
    m_es.moveEntity_NonVarlet(entity_index,{0.0f,m_global_boundary.y-m_es.aabb_max.at(entity_index).y});
  }
}

bool GlobalCollisionConstraint::aabbOverlapCheck(uint32_t id1, uint32_t id2){
  float d1x = m_es.aabb_min[id2].x - m_es.aabb_max[id1].x;
  float d1y = m_es.aabb_min[id2].y- m_es.aabb_max[id1].y;
  float d2x = m_es.aabb_min[id1].x - m_es.aabb_max[id2].x;
  float d2y = m_es.aabb_min[id1].y - m_es.aabb_max[id2].y;

  if (d1x > 0.0f || d1y > 0.0f || d2x > 0.0f || d2y > 0.0f){
    return false;
  }

  return true;
}

void GlobalCollisionConstraint::applyGlobalCollisionResolution(uint32_t id1, uint32_t id2){
  const float COLLISION_DAMPENING = 0.75f;
  if(m_es.entity_types[id1] == PARTICLE && m_es.entity_types[id2] == PARTICLE){
    auto particle1_idx = m_es.getParticleStoreIdx(id1);
    auto particle2_idx = m_es.getParticleStoreIdx(id2);
    
    float dist_squared = m_es.positions[id1].distance_squared(m_es.positions[id2]);
    float min_distance =  m_es.ps.radius[particle1_idx] + m_es.ps.radius[particle2_idx];
    if(dist_squared < min_distance * min_distance) {
    // if(GJK_intersection_test(id1, id2, m_es)){
      float dist = std::sqrt(dist_squared);
      float collision_restitution = (m_es.restitutions[id1] + m_es.restitutions[id2])/2.0f;
      float mass_ratio_1 = m_es.masses[id1]/(m_es.masses[id1]+m_es.masses[id2]);
      float mass_ratio_2 = m_es.masses[id2]/(m_es.masses[id1]+m_es.masses[id2]);
      float delta = (dist - min_distance);
      auto move = (m_es.positions[id1] - m_es.positions[id2]) 
                  * ((delta * COLLISION_DAMPENING / dist)  * (collision_restitution + 1.0f));

      m_es.moveEntity_NonVarlet(id1, move * (-1.0f * mass_ratio_2));
      m_es.moveEntity_NonVarlet(id2, move * mass_ratio_1);
    }
  }
  else {
    auto collision = GJK_intersection_test(id1,id2 ,m_es );
    
    if(std::get<0>(collision)){
      // std::cout<<std::endl;
      // std::cout<<"GJK INTERSECTION FOUND FOR "<< id1 <<" and "<<id2 <<std::endl;
      // m_es.positions[id1] = m_es.old_positions[id1];
      // m_es.positions[id2] = m_es.old_positions[id2];

      auto collision_detail = EPA_collision_details(id1, id2, m_es, std::get<1>(collision));
      float depth = std::get<0>(collision_detail);
      physics_type::Vector2 collision_normal = std::get<1>(collision_detail);

      
      float collision_restitution = (m_es.restitutions[id1] + m_es.restitutions[id2])/2.0f;
      float mass_ratio_1 = m_es.masses[id1]/(m_es.masses[id1]+m_es.masses[id2]);
      float mass_ratio_2 = m_es.masses[id2]/(m_es.masses[id1]+m_es.masses[id2]);
      auto move = collision_normal * ((depth * COLLISION_DAMPENING)  * (collision_restitution + 1.0f));

      m_es.moveEntity_NonVarlet(id1, move * (-1.0f * mass_ratio_2));
      m_es.moveEntity_NonVarlet(id2, move * mass_ratio_1);
      
    }
  }
}

