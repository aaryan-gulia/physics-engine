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
    Vector2 operator+(const Vector2& vec);
    Vector2 operator-(const Vector2& vec);
    void operator+=(const Vector2& vec);
    void operator-=(const Vector2& vec);
    bool const operator==(const Vector2& vec);
    Vector2 operator*(double scalar);
    Vector2 operator/(double scalar);
    float distance(const Vector2& vec1);
    float distance_squared(const Vector2& vec1);
    float length_squared();
    float length();
    Vector2 unit();
};

}

struct AllocationMetrics{
  uint32_t TotalAllocated = 0;
  uint32_t TotalFreed = 0;

  uint32_t CurrentUsage() const {return TotalAllocated - TotalFreed;}
};
static AllocationMetrics s_AllocationMetrics;


void* operator new(size_t size);
void* operator new[](size_t size);
void operator delete(void* memory) noexcept;
void operator delete[](void* memory) noexcept;
