#include"physics.h"

using namespace physics2D;


Vector Vector::operator+(Vector vec){
  return Vector(this->x + vec.x, this->y + vec.y);
}
Vector Vector::operator-(Vector vec){
  return Vector(this->x - vec.x, this->y - vec.y);
}
Vector Vector::operator*(double scalar){
  return Vector(this->x * scalar, this->y * scalar);
}
Vector Vector::operator/(double scalar){
  return Vector(this->x / scalar, this->y / scalar);
}
