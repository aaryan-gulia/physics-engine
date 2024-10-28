#include"Particle.h"


void Particle::varlet(float dt){

  physics_type::Vector2 temp = position;

  if(dt==0.0f){dt=0.0001f;}
  this->position = position * 1.99f - position_old * 0.99f + force/mass * dt * dt;

  this->position_old = temp; 
}

Particle::Particle(physics_type::Vector2 position, float radius):
position(position),position_old(position),radius(radius),mass(1.0f){}

Particle::Particle():Particle({300.0f,100.0f},10.0f){}
