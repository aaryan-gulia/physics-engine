#include"System.h"
#include<iostream>
#include <cmath>
#include <cstdint>

void System::update(float _frame_time=0.0f){
  accumulateForces();
  varlet();
  for(uint32_t i{0}; i < this->sub_steps; ++i){
    satisfyConstraints();
  }
}

void System::varlet(){
  for(auto& particle: objects){
    particle.varlet(this->dt);
  }
}

void System::satisfyConstraints(){
  for(auto& particle: objects){
    physics_type::Vector2 center_to_object = particle.position - this->center;
    float dist = center_to_object.length();
    
    if(dist + particle.radius > this->radius){
      particle.position = this->center + center_to_object.unit() *(this->radius - particle.radius);
    }
  }

  const uint32_t object_count = objects.size();
  for(uint32_t i{0}; i < object_count; ++i){
    Particle& object1 = objects[i];
    
    for(uint32_t k{i+1}; k < object_count; k++){
      Particle& object2 = objects[k];

      physics_type::Vector2 collision_vector = object1.position - object2.position;
      float dist = collision_vector.length();
           
      if(dist < object1.radius + object2.radius){
        float mass_ratio_1 = object1.mass/(object1.mass+object2.mass);
        float mass_ratio_2 = object2.mass/(object1.mass+object2.mass);
        float delta = 0.5f * (dist - object1.radius - object2.radius) *0.75f;

        object1.position -= collision_vector.unit() * delta;
        object2.position += collision_vector.unit() * delta;
      }
    }
  }
}

const std::vector<Particle>& System::getObjects(){
  return this->objects;
}

void System::addObject(physics_type::Vector2 position, float radius){
  objects.emplace_back(Particle(position, radius));
}
void System::addObject(){
  objects.emplace_back();
}

void System::accumulateForces(){
  for(auto& particle: objects){
    particle.force = this->gravity;    
  }
}

float System::getRadius(){
  return this->radius;
}

physics_type::Vector2 System::getCenter(){
  return this->center;
}

