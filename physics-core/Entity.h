#include "Vector.h"
#include <cstdint>

#pragma once

namespace physics_entity {



class Entity{

  physics_type::Vector2& m_position;
  float& m_angle;
  physics_type::Vector2& m_force;
  float& m_mass;
  float& m_restitution; 

  public:
    Entity(physics_type::Vector2& position, 
           float& angle, 
           physics_type::Vector2& force, 
           float& mass, float& restitution): m_position(position), m_angle(angle), m_force(force), 
                                            m_mass(mass), m_restitution(restitution){}

    const physics_type::Vector2& position(){ return m_position; }
    const float& angle(){ return m_angle; }
  // virtual void varlet(float dt) = 0;
  virtual ~Entity() = default;  // Make Entity polymorphic 
};


class Particle : public Entity{
  float& m_radius;
  
  public:
    
    Particle(physics_type::Vector2& position, 
           float& angle, 
           physics_type::Vector2& force, 
           float& mass, float& restitution, float& radius): Entity(position,angle,force,mass,restitution), 
    m_radius(radius){}

    const float& radius(){ return m_radius; }
};

class Rectangle : public Entity{
  float& m_height;
  float& m_width;

  public:
    
    Rectangle(physics_type::Vector2& position, 
           float& angle, 
           physics_type::Vector2& force, 
           float& mass, float& restitution, float& height, float& width): Entity(position,angle,force,mass,restitution), 
    m_height(height), m_width(width){}

    const float& height(){ return m_height; }
    const float& width(){ return m_width; }
};

}
