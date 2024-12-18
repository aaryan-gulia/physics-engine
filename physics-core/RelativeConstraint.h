#include "Constraint.h"

class RelativeConstraint : public Constraint{
  uint32_t m_entity1_id;
  uint32_t m_entity2_id;
  std::shared_ptr<Entity> m_entity1;
  std::shared_ptr<Entity> m_entity2;
  float m_constraint_distance_min;
  float m_constraint_distance_max;
  float m_constraint_distance_min_squared;
  float m_constraint_distance_max_squared;
  float m_constraint_strength;
  bool m_breakable;
  float m_constraint_breakpoint;
  float m_mass_ratio_1;
  float m_mass_ratio_2;
  
  public:
    RelativeConstraint(std::shared_ptr<Entity> entity1, std::shared_ptr<Entity>entity2,
                      float constraint_distance_min, float constraint_distance_max, 
                      float constraint_strength = 1.0f, bool breakable = false, 
                      float constraint_breakpoint = 0.0f): m_entity1(entity1), m_entity2(entity2), 
                                                          m_constraint_distance_min(constraint_distance_min),
                                                          m_constraint_distance_max(constraint_distance_max),
                                                          m_constraint_strength(constraint_strength),
                                                          m_breakable(breakable),
                                                          m_constraint_breakpoint(constraint_breakpoint),
                                                          m_constraint_distance_min_squared(
                                                          constraint_distance_min * constraint_distance_min),
                                                          m_constraint_distance_max_squared(
                                                          constraint_distance_max * constraint_distance_max),
                                                          m_mass_ratio_1(
                                                          entity1->mass / (entity1->mass + entity2->mass)),
                                                          m_mass_ratio_2(
                                                          entity2->mass / (entity1->mass + entity2->mass)){}
    virtual void apply() override;

  private:
    float getDistanceSquared(std::shared_ptr<Particle> particle_entity1, std::shared_ptr<Particle>particle_entity2);
    void applyPush(std::shared_ptr<Particle> particle_entity1, std::shared_ptr<Particle>particle_entity2);
    void applyPull(std::shared_ptr<Particle> particle_entity1, std::shared_ptr<Particle>particle_entity2);
};

class FixedPositionConstraint : public Constraint {
  uint32_t m_entity_id;
  std::shared_ptr<Entity> m_entity;
  physics_type::Vector2 m_fixed_point_min;
  physics_type::Vector2 m_fixed_point_max;
  float m_constraint_strength;
  bool m_breakable;
  float m_constraint_breakpoint;

  public:
    FixedPositionConstraint(std::shared_ptr<Entity> entity, physics_type::Vector2 fixed_point_min, 
                            physics_type::Vector2 fixed_point_max, float constraint_strength = 1.0f, 
                            bool breakable = false, float constraint_breakpoint = false): m_entity(entity),
                            m_fixed_point_min(fixed_point_min), m_fixed_point_max(fixed_point_max), 
                            m_constraint_strength(constraint_strength), m_breakable(breakable), 
                            m_constraint_breakpoint(constraint_breakpoint){}
    virtual void apply() override;

    
};

