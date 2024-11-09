#include "BroadPhaseGrid.h"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <unordered_set>
#include <utility>
#include <iostream>


std::pair<uint32_t,uint32_t> BroadPhaseGrid::getGridFromPosition(physics_type::Vector2 position){
  return std::make_pair(std::max(0.0f,position.x * m_grid_dimensions.first / m_bounds.x),
                        std::max(0.0f,position.y * m_grid_dimensions.second / m_bounds.y));
}

void BroadPhaseGrid::updatedGrid(std::vector<physics_type::Vector2> aabb_min, std::vector<physics_type::Vector2> aabb_max){
  num_entities = aabb_min.size();
  uint32_t dimensions = std::sqrt(num_entities);
  m_grid_dimensions = std::make_pair(dimensions, dimensions );

  m_dense_grid.clear();

  for(uint32_t i = 0; i <  num_entities; i++){
    // if(aabb_min[i].x < -m_bounds.x || aabb_min[i].y < -m_bounds.y
    // || aabb_max[i].x > 2*m_bounds.x || aabb_max[i].y > 2*m_bounds.y){
    //     continue;
    // }
    auto min_grid = getGridFromPosition(aabb_min[i]);
    auto max_grid = getGridFromPosition(aabb_max[i]);

    for(auto x = min_grid.first; x <= max_grid.first; x++){
      for(auto y = min_grid.second;y <= max_grid.second; y++){
        if(m_dense_grid.find({x,y}) != m_dense_grid.end()){
          m_dense_grid.at({x,y}).emplace_back(i);
        }
        else{
          m_dense_grid[{x,y}] = std::vector<uint32_t>{i};
          m_dense_grid[{x,y}].reserve(num_entities);
        }
      }
    }
  }
}


std::unordered_set<uint32_t> BroadPhaseGrid::getBoundaryIndices(){
  std::unordered_set<uint32_t> boundary_indices;
  for(auto grid_cell: m_dense_grid){
    if (grid_cell.first.first == 0 || grid_cell.first.second == 0
    || grid_cell.first.first >= m_grid_dimensions.first - 1
    || grid_cell.first.second >= m_grid_dimensions.second - 1){
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
