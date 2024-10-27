#include"System.h"
#include <cmath>

void System::update(){
  accumulateForces();
  varlet();
  satisfyConstraints();
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
}

const std::vector<Particle>& System::getObjects(){
  return this->objects;
}

void System::addObject(Vector3D position, float radius){
  objects.emplace_back(Particle(position, radius));
}

void System::accumulateForces(){
  for(auto& particle: objects){
    
    particle.force[0] = this->gravity[0]; 
    particle.force[1] = this->gravity[1]; 
    particle.force[2] = this->gravity[2];
     
  }
}


