#include"Vector.h"

struct Particle{
  Vector3D position;
  Vector3D position_old;
  Vector3D velocity;
  Vector3D force;
  const float radius;
  const float mass;

  public:
    Particle(Vector3D position, float radius);
    Particle();
    void varlet(float dt);
    void addForce(Vector3D force);
};
