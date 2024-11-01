#include "BroadPhaseGrid.h"
#include <algorithm>
#include <Eigen/Dense>
#include <cmath>
#include <cstdint>
#include <unordered_set>
#include <utility>


std::pair<uint32_t,uint32_t> BroadPhaseGrid::getGridFromPosition(Eigen::Vector2f position){
  return std::make_pair(position[0] * m_grid_dimensions.first / m_bounds.x, 
                        position[1] * m_grid_dimensions.second / m_bounds.y);
}

void BroadPhaseGrid::updatedGrid(std::vector<Eigen::Vector2f> aabb_min, std::vector<Eigen::Vector2f> aabb_max){
  num_entities = aabb_min.size();
  uint32_t dimentions = std::sqrt(num_entities);
  m_grid_dimensions = std::make_pair(dimentions,dimentions );

  m_dense_grid = {};

  for(uint32_t i = 0; i <  num_entities; i++){
    auto min_grid = getGridFromPosition(aabb_min[i]);
    auto max_grid = getGridFromPosition(aabb_max[i]);
    for(; min_grid.first <= max_grid.first; min_grid.first++){
      for(;min_grid.second <= max_grid.second; min_grid.second++){
        if(m_dense_grid.find(min_grid) != m_dense_grid.end()){
          m_dense_grid.at(min_grid).emplace_back(i);
        }
        else{
          m_dense_grid[min_grid] = std::vector<uint32_t>(i);
          m_dense_grid[min_grid].reserve(100);
        }
      }
    }
  }
}


std::unordered_set<uint32_t> BroadPhaseGrid::getBoundaryIndices(){
  std::unordered_set<uint32_t> boundary_indices;
  for(auto grid_cell: m_dense_grid){
    if (grid_cell.first.first == 0 || grid_cell.first.second == 0){
      for(auto index : grid_cell.second){
        boundary_indices.emplace(index);
      }
    }
  }
  return boundary_indices;
}

std::vector<std::pair<uint32_t,uint32_t >> BroadPhaseGrid::getCollisionIndices(){
  std::vector<std::pair<uint32_t,uint32_t>> collision_index_vector;
  collision_index_vector.reserve(num_entities);
  for(const auto& grid_cell : m_dense_grid){
    uint32_t num_collision_entities = grid_cell.second.size();
    for(uint32_t i = 0; i < num_collision_entities; i++){
      for(uint32_t j = i + 1; j < num_collision_entities; j++){
        collision_index_vector.emplace_back(i,j);
      }
    }
  }

  collision_index_vector.erase(std::unique(collision_index_vector.begin(),collision_index_vector.end()), collision_index_vector.end());

  return collision_index_vector;
}
