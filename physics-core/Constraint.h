#include"Particle.h"
#include <vector>
#include <memory>

class Constraint{
  public: 
    virtual void apply()=0;
    virtual ~Constraint() = default;
};



class GlobalConstraint : public Constraint{
  std::vector<std::shared_ptr<Entity>> & m_entities;
  physics_type::Vector2 m_global_boundary;

  public:
    GlobalConstraint(std::vector<std::shared_ptr<Entity>>& entities, 
                     physics_type::Vector2 global_boundary): m_entities(entities), m_global_boundary(global_boundary){}
    virtual void apply() override;

  private:
    void applyGlobalBoundary(std::shared_ptr<Particle> particle_entity);
    void applyGlobalCollisionResolution(std::shared_ptr<Particle> particle_entity1, std::shared_ptr<Particle> particle_entity2);
    
};


class RelativeConstraint : public Constraint{
  std::shared_ptr<Entity> entity1;
  std::shared_ptr<Entity> entity2;
  float m_constraint_distance_min;
  float m_constraint_distance_max;
  float m_constrain_distance_min_squared;
  float m_constrain_distance_max_squared;
  float m_constraint_strength;
  bool m_breakable;
  float m_constraint_breakpoint;
  float mass_ratio_1;
  float mass_ratio_2;
  
  public:
    RelativeConstraint(std::shared_ptr<Entity> entity1, std::shared_ptr<Entity>entity2,
                      float constraint_distance_min, float constraint_distance_max, 
                      float constraint_strength = 1.0f, bool breakable = false, 
                      float constraint_breakpoint = 0.0f): entity1(entity1), entity2(entity2), 
                                                          m_constraint_distance_min(constraint_distance_min),
                                                          m_constraint_distance_max(constraint_distance_max),
                                                          m_constraint_strength(constraint_strength),
                                                          m_breakable(breakable),
                                                          m_constraint_breakpoint(constraint_breakpoint),
                                                          m_constrain_distance_min_squared(
                                                          constraint_distance_min * constraint_distance_min),
                                                          m_constrain_distance_max_squared(
                                                          constraint_distance_max * constraint_distance_max),
                                                          mass_ratio_1(
                                                          entity1->mass / (entity1->mass + entity2->mass)),
                                                          mass_ratio_2(
                                                          entity2->mass / (entity1->mass + entity2->mass)){}
    virtual void apply() override;

  private:
    float getDistanceSquared(std::shared_ptr<Particle> particle_entity1, std::shared_ptr<Particle>particle_entity2);
    void applyPush(std::shared_ptr<Particle> particle_entity1, std::shared_ptr<Particle>particle_entity2);
    void applyPull(std::shared_ptr<Particle> particle_entity1, std::shared_ptr<Particle>particle_entity2);
};
