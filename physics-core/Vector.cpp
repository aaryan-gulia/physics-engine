#include "Vector.h"
#include <cmath>

using namespace physics_type;

Vector2 Vector2::operator+(Vector2 vec){
    return {this->x + vec.x, this->y + vec.y};
}
Vector2 Vector2::operator-(Vector2 vec){
    return {this->x - vec.x, this->y - vec.y};
}
void Vector2::operator+=(Vector2 vec){
  this->x += vec.x;
  this->y += vec.y;
}
void Vector2::operator-=(Vector2 vec){
  this->x -= vec.x;
  this->y -= vec.y;
}
bool const Vector2::operator==(const Vector2 vec){
  return this->x == vec.x && this->y == vec.y;
}
Vector2 Vector2::operator*(double scalar){
  return Vector2(this->x * scalar, this->y * scalar);
}
Vector2 Vector2::operator/(double scalar){
  return Vector2(this->x / scalar, this->y / scalar);
}
float Vector2::distance(Vector2& vec){
  return std::sqrt(this->distance_squared(vec));
}
float Vector2::distance_squared(Vector2& vec){
  return (this->x - vec.x) * (this->x - vec.x) + (this->y - vec.y) * (this->y - vec.y);
}
float Vector2::length(){
  return std::sqrt(this->x * this->x + this->y * this->y);
}
float Vector2::length_squared(){
  return this->x * this->x + this->y * this->y;
}
Vector2 Vector2::unit(){
  return (*this/this->length());
}

// void* operator new(size_t size){
//   s_AllocationMetrics.TotalAllocated += size;

//   return malloc(size);
// }

// void operator delete(void* memory, size_t size){
//   s_AllocationMetrics.TotalFreed += size;

//   free(memory);
// }
