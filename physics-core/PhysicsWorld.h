#include "Constraint.h"
#include "Vector.h"
#include <cstdint>
#include <memory>
#include <vector>



class PhysicsWorld{
  EntityStore es;
  std::vector<std::shared_ptr<Entity>> entities;
  std::vector<std::shared_ptr<Constraint>> constraints;
  physics_type::Vector2 gravity = {0.0f, 0.5f};
  uint32_t sub_steps = 1;
  float dt = 1.0f/10.0f;

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
  
