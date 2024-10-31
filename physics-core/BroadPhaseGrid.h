#include "Vector.h"
#include <unordered_map>
#include <utility>
#include <vector>


class BroadPhaseGrid{
  public:
    BroadPhaseGrid();
    void updatedGrid(std::vector<std::pair<physics_type::Vector2,physics_type::Vector2>> entityMinMaxVec);
    std::pair<uint32_t,uint32_t> getGridFromPosition(physics_type::Vector2 position);
    
  private:
    std::vector<std::vector<uint32_t>> m_flattened_grid;
    std::unordered_map<std::pair<uint32_t,uint32_t>, std::vector<uint32_t>> m_dense_grid;
    physics_type::Vector2 m_bounds;
    std::pair<uint32_t,uint32_t> m_grid_dimensions;
};
