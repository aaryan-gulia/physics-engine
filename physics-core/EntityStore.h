#include "Vector.h"
#include <cstdint>
#include <vector>


enum EntityType{
  Particle
};

struct ParticleStore{
  std::vector<uint32_t> entity_index;
  std::vector<float> radius;
};

struct EntityStore{
  std::vector<physics_type::Vector2> positions;
  std::vector<physics_type::Vector2> old_positions;
  std::vector<physics_type::Vector2> forces;
  std::vector<float> masses;
  std::vector<float> restitutions;
  std::vector<physics_type::Vector2> aabb_min;
  std::vector<physics_type::Vector2> aabb_max;
  ParticleStore ps;

  void moveEntity_NonVarlet(uint32_t index, physics_type::Vector2 move_vector);
  void setParticleEntityPosition(uint32_t index, physics_type::Vector2 position);
  void applyForce(uint32_t index, physics_type::Vector2 force_vector);
  void updateAABB(uint32_t index);
  void varletStep(float dt);
  void addParticleEntity(float radius, float mass, physics_type::Vector2 position, float restitution = 0.0f);
  void removeParticleEntity(uint32_t idx);
};