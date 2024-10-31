#include"BroadPhaseGrid.h"


std::pair<uint32_t,uint32_t> BroadPhaseGrid::getGridFromPosition(physics_type::Vector2 position){
  return std::make_pair(position.x * m_grid_dimensions.first / m_bounds.x, 
                        position.y * m_grid_dimensions.second / m_bounds.y);
}

void BroadPhaseGrid::updatedGrid(std::vector<std::pair<physics_type::Vector2,physics_type::Vector2>> entityMinMaxVec){
  auto num_entities = entityMinMaxVec.size();
  uint32_t dimension = std::sqrt(num_entities);
  m_grid_dimensions = std::make_pair(dimension, dimension);

  m_flattened_grid = {};
  m_dense_grid = {};
  for(uint32_t i = 0; i < num_entities; i++){
    auto min_grid = getGridFromPosition(entityMinMaxVec[i].first);
    auto max_grid = getGridFromPosition(entityMinMaxVec[i].second);
    for(; min_grid.first <= max_grid.first; min_grid.first++){
      for(;min_grid.second <= max_grid.second; min_grid.second++){
        if(m_dense_grid.find(min_grid) != m_dense_grid.end()){
          m_dense_grid.at(min_grid).push_back(i);
        }
        else{
          m_dense_grid[min_grid] = {i};
        }
      }
    }
  }
}
