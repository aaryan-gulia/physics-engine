#include"physics.h"
#include <algorithm>
#include <cmath>
#include <numeric>
#include <vector>

using namespace physics2D;


Vector Vector::operator+(Vector vec){
  return Vector(this->x + vec.x, this->y + vec.y);
}
Vector Vector::operator-(Vector vec){
  return Vector(this->x - vec.x, this->y - vec.y);
}
bool const Vector::operator==(const Vector vec){
  return this->x == vec.x && this->y == vec.y;
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

RigidBody2DCircle::RigidBody2DCircle(double radius, double mass, Vector center, Vector velocity, Vector gravity):
  radius(radius), mass(mass), center(center), velocity(velocity){
    forces.push_back(gravity);
};

void RigidBody2DCircle::collide(RigidBody2DCircle circle){
 //TODO 
}
    
void System::addRigidBody2DCircle(double radius, double mass, Vector center, Vector velocity){
  if (std::find_if(this->circles.begin(),this->circles.end() ,[&center](RigidBody2DCircle& circle){
               return center == circle.center;
               }) != this->circles.end()) return;
  this->circles.push_back(RigidBody2DCircle(radius,mass,center,velocity,this->gAcceleration * mass));
}

void System::propogate(double d_t){
  if (this->circles.empty()) return;

  for(auto & circle: this->circles){

    if(circle.center.x - circle.radius < 0 && circle.velocity.x < 0) circle.velocity.x = -circle.velocity.x; 
    else if(circle.center.x + circle.radius > this->dimensions.x && circle.velocity.x > 0) circle.velocity.x = -circle.velocity.x; 
    else if(circle.center.y - circle.radius < 0 && circle.velocity.y < 0) circle.velocity.y = -circle.velocity.y; 
    else if(circle.center.y + circle.radius > this->dimensions.y && circle.velocity.y > 0) circle.velocity.y = -circle.velocity.y; 
    else{
    circle.velocity = circle.velocity + std::accumulate(circle.forces.begin(), circle.forces.end(), Vector(0.0,0.0))
                                      / circle.mass * d_t;
    }
    circle.center = circle.center + circle.velocity * d_t;  
  }
}
