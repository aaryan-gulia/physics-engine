#include"Constraint.h"
#include <memory>

void GlobalConstraint::apply(){
  
  for(auto entity: m_entities){
    applyGlobalBoundary(std::dynamic_pointer_cast<Particle>(entity));
  }

  const uint32_t object_count = m_entities.size();
  for(uint32_t i{0}; i < object_count; ++i){
    auto entity1 = this->m_entities[i];
    
    for(uint32_t k{i+1}; k < object_count; k++){
      auto entity2 = this->m_entities[k];
      applyGlobalCollisionResolution(std::dynamic_pointer_cast<Particle>(entity1),
                                     std::dynamic_pointer_cast<Particle>(entity2));
    }
  }
}

void GlobalConstraint::applyGlobalBoundary(std::shared_ptr<Particle> particle_entity){
  if(particle_entity->position.x - particle_entity->radius < 0){
    particle_entity->position.x = particle_entity->radius;
  }
  else if(particle_entity->position.x + particle_entity->radius > this->m_global_boundary.x){
    particle_entity->position.x = this->m_global_boundary.x - particle_entity->radius;
    
  }
  
  if(particle_entity->position.y - particle_entity->radius < 0){
    particle_entity->position.y = particle_entity->radius;
  }
  else if(particle_entity->position.y + particle_entity->radius > this->m_global_boundary.y){
    particle_entity->position.y = this->m_global_boundary.y - particle_entity->radius;
  }
}

void GlobalConstraint::applyGlobalCollisionResolution(std::shared_ptr<Particle> particle_entity1,
                                                      std::shared_ptr<Particle> particle_entity2){
  
      physics_type::Vector2 collision_vector = particle_entity1->position - particle_entity2->position;
      float dist = collision_vector.length();
           
      if(dist < particle_entity1->radius + particle_entity2->radius){
        float collisition_restitiution = (particle_entity1->restitution + particle_entity2->restitution)/2.0f;
        float mass_ratio_1 = particle_entity1->mass/(particle_entity1->mass+particle_entity2->mass);
        float mass_ratio_2 = particle_entity2->mass/(particle_entity1->mass+particle_entity2->mass);
        float delta = (dist - particle_entity1->radius - particle_entity2->radius) * 0.75;

        particle_entity1->position -= collision_vector.unit() * delta * mass_ratio_2 * (collisition_restitiution + 1.0f);
        particle_entity2->position += collision_vector.unit() * delta * mass_ratio_1 * (collisition_restitiution + 1.0f);
      }
}

void RelativeConstraint::apply(){
  float d_2 = getDistanceSquared(std::dynamic_pointer_cast<Particle>(entity1),
                                 std::dynamic_pointer_cast<Particle>(entity2));
  if(d_2 > m_constrain_distance_max_squared){
    applyPull(std::dynamic_pointer_cast<Particle>(entity1),std::dynamic_pointer_cast<Particle>(entity2) );
  }
  else if(d_2 < m_constrain_distance_min_squared){
    applyPush(std::dynamic_pointer_cast<Particle>(entity1),std::dynamic_pointer_cast<Particle>(entity2) );
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
