#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdlib>
namespace physics_type{
  
class Vector2{
  public: 
    float x,y;

  public:
    Vector2() = default;
    Vector2(double x, double y):x(x),y(y){};
    Vector2 operator+(Vector2 vec);
    Vector2 operator-(Vector2 vec);
    void operator+=(Vector2 vec);
    void operator-=(Vector2 vec);
    bool const operator==(Vector2 vec);
    Vector2 operator*(double scalar);
    Vector2 operator/(double scalar);
    float distance(Vector2& vec1);
    float distance_squared(Vector2& vec1);
    float length_squared();
    float length();
    Vector2 unit();
};

}

struct AllocationMetrics{
  uint32_t TotalAllocated = 0;
  uint32_t TotalFreed = 0;

  uint32_t CurrentUsage() {return TotalAllocated - TotalFreed;}
};

static AllocationMetrics s_AllocationMetrics;

// void* operator new(size_t size);
// void operator delete(void* memory, size_t size);
