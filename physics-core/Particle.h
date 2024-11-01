#include"Entity.h"
#include "Vector.h"
#include <utility>

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
        followGlobalBoundaryConstraint), radius(radius){
    physics_type::Vector2 aabb_min = position - physics_type::Vector2{radius,radius};
    physics_type::Vector2 aabb_max = position + physics_type::Vector2{radius, radius};
    aabb = std::make_pair(aabb_min, aabb_max);
  };
};
