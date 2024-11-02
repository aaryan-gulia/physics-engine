#include "Constraint.h"
#include "Vector.h"
#include <cstdint>
#include <memory>
#include <vector>
#include <chrono>


class PhysicsWorld{
  EntityStore es;
  std::vector<std::shared_ptr<Entity>> entities;
  std::vector<std::shared_ptr<Constraint>> constraints;
  physics_type::Vector2 gravity = {0.0f, 1000.0f};
  uint32_t sub_steps = 1;
  std::chrono::time_point<std::chrono::high_resolution_clock> last_varlet_time = std::chrono::high_resolution_clock::now();

  public:
    void update(float frame_time);
    void addEntity(std::shared_ptr<Entity> entity);
    void addConstraint(std::shared_ptr<Constraint> constraint);
    std::vector<std::shared_ptr<Entity>>& getEntities();
    EntityStore& getEs();
    
  private:
    void varlet();
    void satisfyConstraints();
    void accumulateForces();
};
  
