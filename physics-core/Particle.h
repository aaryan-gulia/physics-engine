#include"Vector.h"

struct Particle{
  physics_type::Vector2 position;
  physics_type::Vector2 position_old;
  physics_type::Vector2 velocity;
  physics_type::Vector2 force{0.0f,10.0f};
  const float radius;
  const float mass;

  public:
    Particle(physics_type::Vector2 position, float radius);
    Particle();
    void varlet(float dt);
    void addForce(physics_type::Vector2 force);
};
