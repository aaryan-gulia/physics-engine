#include "Vector.h"
#include "Particle.h"
#include <cstdint>
#include <vector>


class System{
  std::vector<Particle> objects;
  const Vector3D gravity = {0.0f, 0.5f, 0.0f};
  const Vector3D center = {400.0f, 225.0f,0.0f};
  const float radius = 200.0f;
  const uint32_t sub_steps = 10;
  float dt = 1.0f/10.0f;

  public:
    void update(float frame_time);
    void addObject(Vector3D position, float radius);
    void addObject();
    const std::vector<Particle>& getObjects();
    float getRadius();
    std::vector<float> getCenter();
    
  private:
    void varlet();
    void satisfyConstraints();
    void accumulateForces();
};
  
