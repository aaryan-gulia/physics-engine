
#include "Vector.h"

struct Particle{
  Vector3D position;
  Vector3D position_old;
  Vector3D velocity;
  Vector3D force;
  float radius;
  float mass;

  public:
    Particle(Vector3D position, float radius);
    void varlet(float dt);
    void addForce(Vector3D force);
};
