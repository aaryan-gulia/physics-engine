#include "Entity.h"
#include <cstdint>
#include <utility>
#include <vector>
#include <memory>
#include"BroadPhaseGrid.h"
#include "Vector.h"

class Constraint{
  public: 
    virtual ~Constraint() = default;
    virtual void apply() = 0;
};

class GlobalCollisionConstraint : public Constraint{
  EntityStore& m_es;
  std::vector<std::shared_ptr<Entity>> & m_entities;
  std::vector<std::pair<physics_type::Vector2,physics_type::Vector2>> m_aabb_vec;
  physics_type::Vector2 m_global_boundary;
  BroadPhaseGrid m_collision_grid;

  public:
    GlobalCollisionConstraint(std::vector<std::shared_ptr<Entity>>& entities, EntityStore& es, 
                     physics_type::Vector2 global_boundary): m_entities(entities), m_es(es),
                     m_global_boundary(global_boundary), m_collision_grid(global_boundary){}
    virtual void apply() override;

  private:
    bool aabbOverlapCheck(uint32_t id1, uint32_t id2);
    void applyGlobalBoundary(uint32_t entity_index);
    void applyGlobalCollisionResolution(uint32_t id1, uint32_t id2);
    void updateAABBVec();
};


