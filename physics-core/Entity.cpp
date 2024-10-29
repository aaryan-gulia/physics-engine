#include"Entity.h"


 
void Entity::varlet(float dt){

  physics_type::Vector2 temp = position;

  this->position = position * 1.99f - position_old * 0.99f + force/mass * dt * dt;

  this->position_old = temp; 
}
