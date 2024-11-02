#include "EntityStore.h"
#include "Vector.h"
#include <cstdint>

#pragma once

class Entity{

  protected:

  public:
  virtual uint32_t id() = 0;
  // virtual void varlet(float dt) = 0;
  virtual ~Entity() = default;  // Make Entity polymorphic 
};


class Particle : public Entity{
  EntityStore& m_es;
  uint32_t m_id;
  
  public:
    
    Particle(EntityStore& es, float radius, float mass, physics_type::Vector2 position, float restitution = 0.0f):
    m_es(es),m_id(es.positions.size()){
    }
    // void varlet(float dt);
    uint32_t id() override {return m_id;}
    ~Particle() override {
      m_es.removeParticleEntity(m_id);
    }
};

