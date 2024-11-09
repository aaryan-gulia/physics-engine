#include "Vector.h"
#include "EntityStore.h"
#include <algorithm>
#include <array>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <sys/errno.h>
#include <vector>


using namespace physics_type;

std::array<Vector2,4> getRectangleVirtices(const Vector2& position, float width, float height, float angle){

  float cos = std::cos(angle);
  float sin = std::sin(angle);
    
  return{
    Vector2{(position.x + width/2.0f) * cos, (position.y + height/2.0f) * sin},
    Vector2{(position.x + width/2.0f) * cos, (position.y - height/2.0f) * sin},
    Vector2{(position.x - width/2.0f) * cos, (position.y + height/2.0f) * sin},
    Vector2{(position.x - width/2.0f) * cos, (position.y - height/2.0f) * sin},
  };
}

Vector2 getFarthestPointOnParticle(const Vector2& position, float radius, const Vector2& direction){
  return (position + direction * radius);
} 

Vector2 getFarthestPointOnRectangle(const Vector2& position, float width, float height, float angle, const Vector2 direction){
  auto virtices = getRectangleVirtices(position,width,height,angle);
  size_t farthest_virtex = 0;
  size_t curr = 0;
  float max_proj = 0;
  
  for(const auto& virtex: virtices){
    float proj = virtex.dot(direction);
    if(proj > max_proj){
      farthest_virtex = curr;
      max_proj = proj;
    }     
    curr++;
  }

  return virtices[farthest_virtex];
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


bool GJK_intersection_test(uint32_t id1, uint32_t id2, EntityStore& es){
  Vector2 d = {0.0f, 1.0f};
  std::vector<Vector2> simplex;

  
}
