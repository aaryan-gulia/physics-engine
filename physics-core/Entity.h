#include "Vector.h"
#include <cstdint>
#include <emmintrin.h>
#include <utility>
#include <Eigen/Dense>

using Eigen::Vector2f;

struct ParticleStore{
  std::vector<uint32_t> entity_index;
  std::vector<float> radius;
};

struct EntityStore{
  std::vector<Eigen::Vector2f> positions;
  std::vector<Eigen::Vector2f> old_positions;
  std::vector<Eigen::Vector2f> forces;
  std::vector<float> masses;
  std::vector<float> restitutions;
  std::vector<Eigen::Vector2f> aabb_min;
  std::vector<Eigen::Vector2f> aabb_max;
  ParticleStore ps;

  void moveEntity_NonVarlet(uint32_t index, Eigen::Vector2f move_vector);
  void applyForce(uint32_t index, Eigen::Vector2f force_vector);
  void varletStep(float dt);
  void addParticleEntity(float radius, float mass, float position[2], float restitution = 0.0f);
};


struct Entity{
  float mass;
  float restitution;
  physics_type::Vector2 position;
  physics_type::Vector2 position_old;
  physics_type::Vector2 velocity;
  physics_type::Vector2 force;
  bool followGlobalBoundaryConstrain;
  std::pair<physics_type::Vector2,physics_type::Vector2> aabb;

  Entity(float mass, 
         physics_type::Vector2 position, 
         physics_type::Vector2 velocity = {0.0f,0.0f},
         float restitution = 0.0f,
         bool followGlobalBounderyConstrain = true):
        mass(mass),
        position(position),
        position_old(position),
        velocity(velocity),
        restitution(restitution),
        followGlobalBoundaryConstrain(followGlobalBounderyConstrain){};

  void varlet(float dt);
 public:
    virtual ~Entity() = default;  // Make Entity polymorphic 
};
