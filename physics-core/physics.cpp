#include"physics.h"
#include <cmath>

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
double Vector::distance(Vector vec){
  Vector diff = *this - vec;
  return diff.length();
}
double Vector::length(){
  return std::sqrt(this->x * this->x + this->y * this->y);
}

void System::addRigidBody2DCircle(double circumfrence, double mass, Vector center, Vector velocity){
  this->circles.push_back(RigidBody2DCircle(circumfrence,mass,center,velocity));
}
