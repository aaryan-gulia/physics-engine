#include"Particle.h"


void Particle::varlet(float dt){
  
  Vector3D temp = {position[0],position[1],position[2]};
  
  position[0] = position[0] * 2 - position_old[0] + force[0]/mass * dt * dt;
  position[1] = position[1] * 2 - position_old[1] + force[1]/mass * dt * dt;
  position[2] = position[2] * 2 - position_old[2] + force[2]/mass * dt * dt;

  position_old[0] = temp[0];
  position_old[1] = temp[1];
  position_old[2] = temp[2];
}

Particle::Particle(Vector3D position, float radius):
radius(radius), mass(1.0f){
  this->position[0] = position[0];
  this->position[1] = position[1];
  this->position[2] = position[3];
  
  this->position_old[0] = position[0];
  this->position_old[1] = position[1];
  this->position_old[2] = position[3];
}
