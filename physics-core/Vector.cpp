#include "Vector.h"
#include <cmath>
#include <iostream>

using namespace physics_type;

Vector2 Vector2::operator+(const Vector2& vec) const{
    return {this->x + vec.x, this->y + vec.y};
}
Vector2 Vector2::operator-(const Vector2& vec) const{
    return {this->x - vec.x, this->y - vec.y};
}
void Vector2::operator+=(const Vector2& vec){
  this->x += vec.x;
  this->y += vec.y;
}
void Vector2::operator-=(const Vector2& vec){
  this->x -= vec.x;
  this->y -= vec.y;
}
bool Vector2::operator==(const Vector2& vec) const{
  return this->x == vec.x && this->y == vec.y;
}
Vector2 Vector2::operator*(double scalar) const{
  return {this->x * scalar, this->y * scalar};
}
Vector2 Vector2::operator/(double scalar) const{
  return {this->x / scalar, this->y / scalar};
}
float Vector2::distance(const Vector2& vec) const{
  return std::sqrt(this->distance_squared(vec));
}
float Vector2::distance_squared(const Vector2& vec) const{
  return (this->x - vec.x) * (this->x - vec.x) + (this->y - vec.y) * (this->y - vec.y);
}
float Vector2::length() const{
  return std::sqrt(this->x * this->x + this->y * this->y);
}
float Vector2::length_squared(){
  return this->x * this->x + this->y * this->y;
}
Vector2 Vector2::unit() const{
  return (*this/this->length());
}

float Vector2::dot(const Vector2& vec) const{
  return (x * vec.x + y * vec.y);
}

Vector2 Vector2::triple_product(const Vector2& vec2, const Vector2& vec3) const{
  return {y * (vec2.x * vec3.y - vec3.x * vec2.y), x * (vec2.y * vec3.x - vec3.y * vec2.x)};
}

