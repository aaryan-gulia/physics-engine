#include"Entity.h"

struct Particle:Entity{
  const float radius;

  public:
  Particle(float radius, float mass, 
         physics_type::Vector2 position, 
         physics_type::Vector2 velocity = {0.0f,0.0f},
         float restitution = 0.0f,
         bool followGlobalBoundaryConstraint = true):
        Entity(mass,
        position,
        velocity,
        restitution,
        followGlobalBoundaryConstraint), radius(radius){};
};
