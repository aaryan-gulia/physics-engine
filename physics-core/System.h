#include "Particle.h"
#include <cstdint>
#include <vector>


class System{
  std::vector<Particle> objects;
  physics_type::Vector2 gravity = {0.0f, 0.5f};
  physics_type::Vector2 center = {400.0f, 225.0f};
  float radius = 200.0f;
  uint32_t sub_steps = 5;
  float dt = 1.0f/10.0f;

  public:
    void update(float frame_time);
    void addObject(physics_type::Vector2 position, float radius);
    void addObject();
    const std::vector<Particle>& getObjects();
    float getRadius();
    physics_type::Vector2 getCenter();
    
  private:
    void varlet();
    void satisfyConstraints();
    void accumulateForces();
};
  
