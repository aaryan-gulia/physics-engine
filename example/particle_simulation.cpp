#include"PhysicsWorld.h"
#include "raylib.h"
#include <cstdint>
#include <iostream>
#include <memory>


extern const float PARTICLE_RADIUS = 10.0f;
extern const float WINDOW_HEIGHT = 450.0f;
extern const float WINDOW_WIDTH = 800.0f;
 
PhysicsWorld setup(){
  PhysicsWorld world;
  float window[2] = {WINDOW_WIDTH,WINDOW_HEIGHT};
  world.addConstraint(std::make_shared<GlobalCollisionConstraint>(
                      GlobalCollisionConstraint(world.getEntities(),world.getEs(), window)));
  return world;
}



std::shared_ptr<Particle> addParticle(float x, float y, PhysicsWorld & world){
  auto particle = std::make_shared<Particle>(Particle(PARTICLE_RADIUS, 1.0f, {x,y}));
  world.addEntity(particle);
  float pos[2] = {x,y};
  world.getEs().addParticleEntity(PARTICLE_RADIUS, 1.0f, pos);
  return particle;
}



std::vector<std::shared_ptr<Particle>> addParticleChain(float x_begin, float y_begin, float x_end, float y_end, 
                                                        PhysicsWorld & world){
  float distance = physics_type::Vector2{x_begin - x_end, y_begin - y_end}.length();
  uint32_t num_particles = distance/(PARTICLE_RADIUS * 2);

  std::vector<std::shared_ptr<Particle>> particles = {
    std::make_shared<Particle>(Particle(PARTICLE_RADIUS,1.0f,{x_begin,y_begin}))
  };

  world.addEntity(particles[0]);
  
  for(uint32_t i = 1; i < num_particles; i++){
    auto particle = std::make_shared<Particle>(Particle(PARTICLE_RADIUS,1.0f, 
                                                               {x_begin + (x_end - x_begin) * i / num_particles,
                                                             y_begin + (y_end - y_begin) * i / num_particles}));
    world.addEntity(particle);
    particles.push_back(particle);
  } 
  
  num_particles = particles.size();
  if(num_particles >= 2){
    // world.addConstraint(std::make_shared<FixedPositionConstraint>(
    //                       FixedPositionConstraint(particles.front(),particles.front()->position,particles.front()->position)));
    // world.addConstraint(std::make_shared<FixedPositionConstraint>(
    //                       FixedPositionConstraint(particles.back(),
    //                                               particles.back()->position,
    //                                               particles.back()->position)));
    for(uint32_t i = 0; i < particles.size()-1; i++){
      world.addConstraint(std::make_shared<RelativeConstraint>(
                            RelativeConstraint(particles[i],particles[i+1],0.0f,PARTICLE_RADIUS*1.99f,0.2f)));
    }
  }
  return particles;
}

void addRigidBody(float x, float y, PhysicsWorld& world){
  auto chain1 = addParticleChain(x, y, x+PARTICLE_RADIUS*10,y ,world );
  auto chain2 = addParticleChain(x,y+2*PARTICLE_RADIUS ,x+PARTICLE_RADIUS*10 ,y+2*PARTICLE_RADIUS , world);
  auto chain3 = addParticleChain(x,y+4*PARTICLE_RADIUS ,x+PARTICLE_RADIUS*10 ,y+4*PARTICLE_RADIUS , world);

  for(uint32_t i = 0; i< chain1.size(); i++){
    world.addConstraint(
      std::make_shared<RelativeConstraint>(RelativeConstraint(chain1[i],chain2[i],0.0f,PARTICLE_RADIUS*1.99f,0.2f))
    );
    world.addConstraint(
      std::make_shared<RelativeConstraint>(RelativeConstraint(chain2[i],chain3[i],0.0f,PARTICLE_RADIUS*1.99f,0.2f))
    );
  }
}


