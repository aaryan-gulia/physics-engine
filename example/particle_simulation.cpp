#include"PhysicsWorld.h"
#include <cstdint>
#include <memory>


extern const float PARTICLE_RADIUS = 20.0f;
extern const float WINDOW_HEIGHT = 450.0f;
extern const float WINDOW_WIDTH = 800.0f;
 
PhysicsWorld setup(){
  PhysicsWorld world;
  world.addConstraint(std::make_shared<GlobalConstraint>(
                      GlobalConstraint(world.getEntities(), {WINDOW_WIDTH, WINDOW_HEIGHT})));
  return world;
}



std::shared_ptr<Particle> addParticle(float x, float y, PhysicsWorld & world){
  auto particle = std::make_shared<Particle>(Particle(PARTICLE_RADIUS, 1.0f, {x,y}));
  world.addEntity(particle);
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
                                                               {x_begin + PARTICLE_RADIUS*2.0f*i,
                                                             y_begin}));
    world.addEntity(particle);
    particles.push_back(particle);
  } 
  
  num_particles = particles.size();
  if(num_particles >= 2){
    world.addConstraint(std::make_shared<FixedPositionConstraint>(
                          FixedPositionConstraint(particles.front(),particles.front()->position,particles.front()->position)
                        ));
    world.addConstraint(std::make_shared<FixedPositionConstraint>(
                          FixedPositionConstraint(particles.back(),
                                                  particles.back()->position,
                                                  particles.back()->position)
                        ));
    for(uint32_t i = 0; i < particles.size()-1; i++){
      world.addConstraint(std::make_shared<RelativeConstraint>(
                            RelativeConstraint(particles[i],particles[i+1],0.0f,PARTICLE_RADIUS*2.0f,0.1f)
                          ));
    }
  }
  return particles;
}


