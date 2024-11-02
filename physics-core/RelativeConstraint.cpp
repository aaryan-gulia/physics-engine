#include "RelativeConstraint.h"

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
