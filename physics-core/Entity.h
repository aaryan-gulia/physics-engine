#include "EntityStore.h"
#include "Vector.h"
#include <cstdint>


class Entity{
  EntityStore& m_es;
  uint32_t m_id;

  public:
  Entity(EntityStore& es, uint32_t id):m_es(es),m_id(id){}
  virtual void varlet(float dt) = 0;
  virtual ~Entity() = default;  // Make Entity polymorphic 
};


class Particle : public Entity{
  public:

    Particle(EntityStore& es, float radius, float mass, physics_type::Vector2 position, float restitution = 0.0f):
    Entity(es,es.positions.size()){
      es.addParticleEntity(radius,mass,position,restitution);
    }
    void varlet(float dt);
    ~Particle(){
      m_es.restitutions;
    }
};

