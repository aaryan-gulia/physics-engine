#include "Vector.h"
#include "Particle.h"
#include <cstdint>
#include <vector>


class System{
  std::vector<Particle> objects;
  Vector3D gravity = {0.0f, 100.0f, 0.0f};
  Vector3D center = {400.0f, 225.0f,0.0f};
  float radius = 200.0f;
  uint32_t sub_steps = 10;
  float dt = 1.0f/500.0f;

  public:
    void update();
    void addObject(Vector3D position, float radius);
    const std::vector<Particle>& getObjects();
    
  private:
    void varlet();
    void satisfyConstraints();
    void accumulateForces();
};
  
