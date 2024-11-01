#include"Constraint.h"
#include <memory>

void GlobalCollisionConstraint::apply(){
  m_collision_grid.updatedGrid(m_es.aabb_min, m_es.aabb_max);
  auto boundaryEntities = m_collision_grid.getBoundaryIndices();
  //auto collisionEntities = m_collision_grid.getCollisionIndices();

  for(auto entity: boundaryEntities){
    applyGlobalBoundary(entity);
  }

  for(auto grid_cell: m_collision_grid.m_dense_grid){
    auto collisionEntities = grid_cell.second;
    for(uint32_t i = 0; i < collisionEntities.size(); i++){
      for(uint32_t j = i + 1; j < collisionEntities.size(); j++){
        applyGlobalCollisionResolution(collisionEntities[i],collisionEntities[j]);
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

void GlobalCollisionConstraint::applyGlobalCollisionResolution(uint32_t id1, uint32_t id2){
  
      auto collision_vector = m_es.positions[id1] - m_es.positions[id2];
      float dist = collision_vector.length();
           
      if(dist < m_es.ps.radius[id1] + m_es.ps.radius[id2]){
        float collision_restitution = (m_es.restitutions[id1] + m_es.restitutions[id2])/2.0f;
        float mass_ratio_1 = m_es.masses[id1]/(m_es.masses[id1]+m_es.masses[id2]);
        float mass_ratio_2 = m_es.masses[id2]/(m_es.masses[id1]+m_es.masses[id2]);
        float delta = (dist - m_es.ps.radius[id1] - m_es.ps.radius[id2]) * 0.75;
        auto move = collision_vector / dist * delta * mass_ratio_1 * (collision_restitution + 1.0f);

        m_es.moveEntity_NonVarlet(id1, move * -1.0f);
        m_es.moveEntity_NonVarlet(id2, move );

      }
}

void RelativeConstraint::apply(){
  float d_2 = getDistanceSquared(std::dynamic_pointer_cast<Particle>(m_entity1),
                                 std::dynamic_pointer_cast<Particle>(m_entity2));
  if(d_2 > m_constraint_distance_max_squared){
    applyPull(std::dynamic_pointer_cast<Particle>(m_entity1),std::dynamic_pointer_cast<Particle>(m_entity2) );
  }
  else if(d_2 < m_constraint_distance_min_squared){
    applyPush(std::dynamic_pointer_cast<Particle>(m_entity1),std::dynamic_pointer_cast<Particle>(m_entity2) );
    }
}

float RelativeConstraint::getDistanceSquared(std::shared_ptr<Particle>particle_entity1, std::shared_ptr<Particle>particle_entity2){
  return particle_entity1->position.distance_squared(particle_entity2->position);
}

void RelativeConstraint::applyPush(std::shared_ptr<Particle>particle_entity1, std::shared_ptr<Particle>particle_entity2){
  float distance = particle_entity1->position.distance(particle_entity2->position);
  float delta = (m_constraint_distance_min - distance) * m_constraint_strength;
  auto unit_vec = particle_entity1->position - particle_entity2->position;
  
  particle_entity1->force += unit_vec * delta;
  particle_entity2->force -= unit_vec * delta;
}

void RelativeConstraint::applyPull(std::shared_ptr<Particle>particle_entity1, std::shared_ptr<Particle>particle_entity2){
  float distance = particle_entity1->position.distance(particle_entity2->position);
  float delta = (distance - m_constraint_distance_max) * m_constraint_strength;
  auto unit_vec = particle_entity1->position - particle_entity2->position;

  particle_entity1->force -= unit_vec * delta;
  particle_entity2->force += unit_vec * delta;
}



void FixedPositionConstraint::apply(){
  if(m_entity->position.x < m_fixed_point_min.x){
    m_entity->position.x = m_fixed_point_min.x;
  }
  if(m_entity->position.y < m_fixed_point_min.y){
    m_entity->position.y = m_fixed_point_min.y;
  }
  if(m_entity->position.x > m_fixed_point_max.x){
    m_entity->position.x = m_fixed_point_max.x;
  }
  if(m_entity->position.y > m_fixed_point_max.y){
    m_entity->position.y = m_fixed_point_max.y;
  }
}
