#include "Vector.h"
#include <cstdint>
#include <vector>
#include <iostream>


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

  EntityStore(){
      positions.reserve(1000);
      old_positions.reserve(1000);
        forces.reserve(1000);
        masses.reserve(1000);
        restitutions.reserve(1000);
        aabb_min.reserve(1000);
        aabb_max.reserve(1000);
        ps.entity_index.reserve(1000);
        ps.radius.reserve(1000);

      // Log the initial state of the positions vector
      std::cout << "Initial size of positions: " << positions.size() << std::endl;
  }

  void moveEntity_NonVarlet(uint32_t index, const physics_type::Vector2& move_vector);
  void setParticleEntityPosition(uint32_t index, const physics_type::Vector2& position);
  void applyForce(uint32_t index, const physics_type::Vector2& force_vector);
  void updateAABB(uint32_t index);
  void varletStep(float dt);
  void addParticleEntity(float radius, float mass, const physics_type::Vector2& position, float restitution = 0.0f);
  void removeParticleEntity(uint32_t idx);
  void clearForces();
};
