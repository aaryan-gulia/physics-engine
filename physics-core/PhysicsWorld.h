#include "Constraint.h"
#include "Vector.h"
#include <cstdint>
#include <memory>
#include <vector>
#include <chrono>


class PhysicsWorld{
  EntityStore es;
  std::vector<Entity*> entities;
  std::vector<std::shared_ptr<Constraint>> constraints;
  physics_type::Vector2 gravity = {0.0f, 1000.0f};
  uint32_t sub_steps = 1;
  std::chrono::time_point<std::chrono::high_resolution_clock> last_varlet_time = std::chrono::high_resolution_clock::now();

  public:
    void update(float frame_time);

    // Returns the Index of the entity from es (EntityStore). User must use the index to access entity;
    uint32_t addParticleEntity(float radius, float mass, float x_position, float y_position, float restitution = 0.0f);

    void removeEntity(uint32_t index);
    void addForceToEntity(uint32_t index, float x_force, float y_force);
    
    void addConstraint(std::shared_ptr<Constraint> constraint);
    EntityStore& getEs();
    
  private:
    void varlet();
    void satisfyConstraints();
    void accumulateForces();
};
  
