#include "Vector.h"

struct Entity{
  float mass;
  float restitution;
  physics_type::Vector2 position;
  physics_type::Vector2 position_old;
  physics_type::Vector2 velocity;
  physics_type::Vector2 force;
  bool followGlobalBoundaryConstrain;

  Entity(float mass, 
         physics_type::Vector2 position, 
         physics_type::Vector2 velocity = {0.0f,0.0f},
         float restitution = 0.0f,
         bool followGlobalBounderyConstrain = true):
        mass(mass),
        position(position),
        position_old(position),
        velocity(velocity),
        restitution(restitution),
        followGlobalBoundaryConstrain(followGlobalBounderyConstrain){};

  void varlet(float dt);
 public:
    virtual ~Entity() = default;  // Make Entity polymorphic 
};
