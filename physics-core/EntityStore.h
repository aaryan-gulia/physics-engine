#include "Vector.h"
#include "Entity.h"
#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>
#include <iostream>


enum EntityType{
  PARTICLE,
  RECTANGLE,
};

struct ParticleStore{
  std::vector<uint32_t> entity_index;
  std::vector<float> radius;
};

struct RectangleStore{
  std::vector<uint32_t> entity_index;
  std::vector<float> width;
  std::vector<float>height;
};


struct EntityStore{

  std::vector<EntityType> entity_types;
  std::vector<physics_type::Vector2> positions;
  std::vector<physics_type::Vector2> old_positions;
  std::vector<float> angle;
  std::vector<float> old_angle;
  std::vector<physics_type::Vector2> forces;
  std::vector<float> torques;
  std::vector<float> masses;
  std::vector<float> moment_of_inertia;
  std::vector<float> restitutions;
  std::vector<physics_type::Vector2> aabb_min;
  std::vector<physics_type::Vector2> aabb_max;
  ParticleStore ps;
  RectangleStore rs;

  EntityStore() = default;

  void moveEntity_NonVarlet(uint32_t index, const physics_type::Vector2& move_vector);
  void setParticleEntityPosition(uint32_t index, const physics_type::Vector2& position);
  void applyForce(uint32_t index, const physics_type::Vector2& force_vector);
  void varletStep(float dt, float dampening_coef);
  void addParticleEntity(float radius, float mass, const physics_type::Vector2& position, float restitution = 0.0f);
  void addRectangleEntity(float width, float height, float mass, const physics_type::Vector2& positions, float restitution = 0.0f);
  void removeEntity(uint32_t idx);
  void clearForces();

  // Entity Interfaces
  std::unique_ptr<physics_entity::Entity> getEntity(uint32_t idx);
  size_t getParticleStoreIdx(uint32_t idx) const;
  size_t getRectangleStoreIdx(uint32_t idx) const;


  private: 
  void addEntity(float mass, float restitution, float position, const physics_type::Vector2& aabb_min,
                 const physics_type::Vector2& aabb_max, float angle);
  void removeParticleEntity(uint32_t idx);
  void removeRectangleEntity(uint32_t idx);
  void updateParticleAABB(uint32_t index);
  void updateRectangleAABB(uint32_t index);

  // Entity Interfaces
  std::unique_ptr<physics_entity::Particle> getParticle(uint32_t idx);
  std::unique_ptr<physics_entity::Rectangle> getRectangle(uint32_t idx);
};
