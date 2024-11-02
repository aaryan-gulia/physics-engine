#include "Vector.h"
#include <cstdint>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        // Mainly for demonstration purposes, i.e. works but is overly simple
        // In the real world, use sth. like boost.hash_combine
        return h1 ^ h2;  
    }
};

class BroadPhaseGrid{
  public:
    BroadPhaseGrid(physics_type::Vector2 bounds):m_bounds(bounds){};
    void updatedGrid(std::vector<physics_type::Vector2> aabb_min, std::vector<physics_type::Vector2> aabb_max);
    std::pair<uint32_t,uint32_t> getGridFromPosition(physics_type::Vector2 position);
    std::unordered_set<uint32_t> getBoundaryIndices();
    std::vector<std::pair<uint32_t,uint32_t> > getCollisionIndices();
        
  private:
    std::vector<std::vector<uint32_t>> m_flattened_grid;
public:
    std::unordered_map<std::pair<uint32_t,uint32_t>, std::vector<uint32_t>, pair_hash> m_dense_grid;
private:
    physics_type::Vector2 m_bounds;
    std::pair<uint32_t,uint32_t> m_grid_dimensions;
    uint32_t num_entities;
};
