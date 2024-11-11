#include "CollisionSolver.h"
#include "Vector.h"
#include <algorithm>
#include <array>
#include <atomic>
#include <cfloat>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <sys/errno.h>
#include <tuple>
#include <utility>
#include <vector>

const float TOLERANCE = 0.0001;

using namespace physics_type;
std::array<Vector2, 4> getRectangleVertices(const Vector2& position, float width, float height, float angle) {
    float cosTheta = std::cos(angle);
    float sinTheta = std::sin(angle);

    std::array<Vector2, 4> vertices = {
            Vector2{position.x + (width / 2.0f) * cosTheta - (height / 2.0f) * sinTheta,
                    position.y + (width / 2.0f) * sinTheta + (height / 2.0f) * cosTheta},
            Vector2{position.x + (width / 2.0f) * cosTheta + (height / 2.0f) * sinTheta,
                    position.y - (width / 2.0f) * sinTheta - (height / 2.0f) * cosTheta},
            Vector2{position.x - (width / 2.0f) * cosTheta + (height / 2.0f) * sinTheta,
                    position.y - (width / 2.0f) * sinTheta - (height / 2.0f) * cosTheta},
            Vector2{position.x - (width / 2.0f) * cosTheta - (height / 2.0f) * sinTheta,
                    position.y + (width / 2.0f) * sinTheta + (height / 2.0f) * cosTheta}
    };

    return vertices;
}

// std::array<Vector2,4> getRectangleVertices(const Vector2& position, float width, float height, float angle){

//   float cos = std::cos(angle);
//   float sin = std::sin(angle);
//   return{
//     Vector2{(position.x + width/2.0f) * cos, (position.y + height/2.0f )* sin},
//     Vector2{(position.x + width/2.0f) * cos, (position.y - height/2.0f )* sin},
//     Vector2{(position.x - width/2.0f) * cos, (position.y + height/2.0f )* sin},
//     Vector2{(position.x - width/2.0f) * cos, (position.y - height/2.0f )* sin},
//   };
// }

Vector2 getFarthestPointOnParticle(const Vector2& position, float radius, const Vector2& direction){
  return (position + direction * radius);
} 

Vector2 getFarthestPointOnRectangle(const Vector2& position, float width, float height, float angle, const Vector2 direction){
  auto vertices = getRectangleVertices(position,width,height,angle);
  size_t farthest_virtex = 0;
  size_t curr = 0;
  float max_proj = vertices[0].dot(direction);
  
  for(const auto& virtex: vertices){
    float proj = virtex.dot(direction);
    if(proj > max_proj){
      farthest_virtex = curr;
      max_proj = proj;
    }

    curr++;

  }

  return vertices[farthest_virtex];
}

Vector2 getFarthestPointOnEntity(uint32_t id, const EntityStore& es, const Vector2& direction){
  if(es.entity_types[id] == PARTICLE){
    return getFarthestPointOnParticle(es.positions[id], es.ps.radius[es.getParticleStoreIdx(id)], direction);
  }
  else if(es.entity_types[id] == RECTANGLE){
    auto rect_idx = es.getRectangleStoreIdx(id);
    return getFarthestPointOnRectangle(es.positions[id],
                                       es.rs.width[rect_idx], es.rs.height[rect_idx], es.angle[id], direction);
  }
}

bool containsOrigin(std::vector<Vector2>& simplex, Vector2& direction){
  auto a_ptr = simplex.end() - 1;
  auto b_ptr = simplex.begin() + 1;
  auto c_ptr = simplex.begin();
  
  auto a = simplex.back();
  auto ao = a * -1;

  if(simplex.size() == 3){
    auto b = simplex[1];
    auto c = simplex[0]; 
    auto ab = b - a;
    auto ac = c - a;

    auto ab_perp = ac.triple_product(ab, ab);
    auto ac_perp = ab.triple_product(ac, ac);

    if (ab_perp.dot(ao) < 0){
      simplex.erase(c_ptr);
      direction = ab_perp;
    }
    else{
      if(ac_perp.dot(ao) < 0){
        simplex.erase(b_ptr);
        direction = ac_perp;
      }
      else{
        return true;
      }
    } 
  }
  else{
    auto b = simplex[0];
    auto ab = b - a;
    auto ab_perp = ab.triple_product(ao, ab);
    direction = std::move(ab_perp);
  }
  return false;
}

bool addToSimplex(std::vector<Vector2>& simplex, Vector2& direction, uint32_t id1, uint32_t id2, EntityStore& es){
  direction = direction.unit();
  simplex.emplace_back(getFarthestPointOnEntity(id1, es, direction) - getFarthestPointOnEntity(id2, es, direction * -1));
  if(simplex.back().dot(direction) < 0){
    return false;
  }
  return true;
}

std::tuple<bool,std::vector<Vector2>> GJK_intersection_test(uint32_t id1, uint32_t id2, EntityStore& es){

  // Implementation from: https://dyn4j.org/2010/04/gjk-gilbert-johnson-keerthi/
  
  Vector2 d = (es.positions[id1] - es.positions[id2]);
  std::vector<Vector2> simplex;

  if(!addToSimplex(simplex, d, id1, id2, es)){
    // return false;
  }
  d = d * -1;

  do{
    if(!addToSimplex(simplex, d, id1, id2, es)){
      return std::tuple<bool,std::vector<Vector2>>(false, simplex);
    }
  }while(!containsOrigin(simplex, d));
  
  return std::tuple<bool,std::vector<Vector2>>(true, simplex);
}



std::tuple<float, Vector2, uint32_t> getClosestEdge(const std::vector<Vector2>& simplex){
  float closest_distance = FLT_MAX;
  Vector2 closest_normal;
  uint32_t closest_index;

  for(uint32_t i = 0; i < simplex.size(); i++){
    uint32_t j = i + 1 == simplex.size() ? 0 : i + 1;

    Vector2 a = simplex[i];
    Vector2 b = simplex[j];

    Vector2 edge = b - a;

    // origin to edge normal
    Vector2 n = edge.triple_product(a, edge).unit();
    float dist = n.dot(a);

    if (dist < closest_distance){
      closest_distance = dist;
      closest_normal = n;
      closest_index = j;
    }
  }

  return std::make_tuple(closest_distance,closest_normal,closest_index);
}

std::tuple<float, Vector2> EPA_collision_details(uint32_t id1, uint32_t id2, const EntityStore& es, std::vector<Vector2>& simplex){

  while(true){
    auto edge = getClosestEdge(simplex);
    Vector2 p = getFarthestPointOnEntity(id1, es, std::get<1>(edge)) - getFarthestPointOnEntity(id2, es, std::get<1>(edge) * -1);
    float dist = p.dot(std::get<1>(edge));
    if(dist - std::get<0>(edge) < TOLERANCE){
      return std::make_tuple(dist, std::get<1>(edge));
    }
    else{
      simplex.insert(simplex.begin() + std::get<2>(edge), p);
    }
  }
}
