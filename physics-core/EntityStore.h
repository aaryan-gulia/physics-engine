#include "Vector.h"
#include <cstdint>
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
  std::vector<float> masses;
  std::vector<float> restitutions;
  std::vector<physics_type::Vector2> aabb_min;
  std::vector<physics_type::Vector2> aabb_max;
  ParticleStore ps;
  RectangleStore rs;

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
  void addRectangleEntity(float width, float height, float mass, const physics_type::Vector2& positions, float restitution = 0.0f);
  void removeEntity(uint32_t idx);
  void clearForces();


  private: 
    void addEntity(float mass, float restitution, float position, const physics_type::Vector2& aabb_min, 
                   const physics_type::Vector2& aabb_max, float angle);
  void removeParticleEntity(uint32_t idx);
  void removeRectangleEntity(uint32_t idx);
};
