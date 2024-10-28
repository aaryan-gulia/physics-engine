#include"System.h"
#include<iostream>
#include <cmath>
#include <cstdint>

void System::update(float frame_time){
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
    Vector3D center_to_object = {
      particle.position[0] - this->center[0],
      particle.position[1] - this->center[1],
      particle.position[2] - this->center[2]
    };

    float dist = std::sqrt((center_to_object[0] * center_to_object[0] +
      center_to_object[1] * center_to_object[1] +
      center_to_object[2] * center_to_object[2]));
    
    if(dist + particle.radius > this->radius){
      particle.position[0] = this->center[0] + center_to_object[0]/dist * (this->radius - particle.radius);
      particle.position[1] = this->center[1] + center_to_object[1]/dist * (this->radius - particle.radius);
      particle.position[2] = this->center[2] + center_to_object[2]/dist * (this->radius - particle.radius);
    }
  }

  const uint32_t object_count = objects.size();
  for(uint32_t i{0}; i < object_count; ++i){
    Particle& object1 = objects[i];
    
    for(uint32_t k{i+1}; k < object_count; k++){
      Particle& object2 = objects[k];

      Vector3D collision_vector = {
        object1.position[0] - object2.position[0],
        object1.position[1] - object2.position[1],
        object1.position[2] - object2.position[2]
      };
      float dist = std::sqrt((collision_vector[0] * collision_vector[0] +
        collision_vector[1] * collision_vector[1]));
      if(dist < object1.radius + object2.radius){
        float mass_ratio_1 = object1.mass/(object1.mass+object2.mass);
        float mass_ratio_2 = object2.mass/(object1.mass+object2.mass);
        float delta = (dist - object1.radius - object2.radius) *1.0f;

        object1.position[0] -= collision_vector[0]/dist * delta;
        object1.position[1] -= collision_vector[1]/dist * delta;
        object1.position[2] -= collision_vector[2]/dist * delta;

        object2.position[0] += collision_vector[0]/dist * delta;
        object2.position[1] += collision_vector[1]/dist * delta;
        object2.position[2] += collision_vector[2]/dist * delta;
      }
    }
  }
}

const std::vector<Particle>& System::getObjects(){
  return this->objects;
}

void System::addObject(Vector3D position, float radius){
  objects.emplace_back(Particle(position, radius));
}
void System::addObject(){
  objects.emplace_back();
}

void System::accumulateForces(){
  for(auto& particle: objects){
    
    particle.force[0] = this->gravity[0]; 
    particle.force[1] = this->gravity[1]; 
    particle.force[2] = this->gravity[2];
     
  }
}

float System::getRadius(){
  return this->radius;
}

std::vector<float> System::getCenter(){
  return std::vector<float>({center[0],center[1],center[2]});
}

