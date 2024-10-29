//this is not functional code
//it is a representation of an idea for what I want the physics-engine library to be used like



int physics_simulation(){
  PhysiceWorld world = PhysicsWorld(AABBoX(height, width),gravity,bounded=true);
  
  std::vector<&Particle> chain_particles; 
  for(int i =0; i<10;i++){
    Particle particle = Particle(position, radius, mass)
    chain_particles.push_back(&particle);
    world.entities.push_back(particle); 
  }  

  chain_particles[0].add_global_constrain(fixed_position1,strength1);
  chain_particles[chain_particles.size()-1].add_global_constrain(fixed_position2,strength2);
  for (int i = 1; i < chain_particles.size()-1; i++){
    chain_particles[i].add_relative_constrain(chain_particle[i-1],distance,strength);
    chain_particles[i].add_relative_constrain(chain_particle[i+1],distance,strength);
  }

  world.entities.emplace_back(AABBoX(point1, point2, mass));
  world.entities.emplace_back(BoX(point1, point2, point3, point4, mass));
  world.QuartetOptimisation(ON, min_grid_width, min_grid_height);

  for(true){
    world.step();
    auto all_entities = world.getEntities();
    //draw entities or do anything else.
  }
}
