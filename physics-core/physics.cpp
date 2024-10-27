#include"physics.h"
#include <algorithm>
#include <cmath>
#include <numeric>
#include <vector>
#include <iostream>


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
Vector Vector::unit(){
  return (*this/this->length());
}

RigidBody2DCircle::RigidBody2DCircle(double radius, double mass, Vector center, Vector velocity, Vector gravity):
  radius(radius), mass(mass), center(center), velocity(velocity), center_prev(center-velocity/500.0){
    forces.push_back(gravity);
};

void RigidBody2DCircle::collide(RigidBody2DCircle &circle) {
    Vector delta = circle.center - this->center;
    double distance = delta.length();
    double overlap = 0.5f * (distance - this->radius - circle.radius);

    if (distance == 0) {
        // Prevent division by zero
        delta = Vector(1.0, 0.0);
        distance = 1.0;
    }

    // Displace current circle
    this->center = this->center - delta.unit() * (overlap);
    // Displace the other circle
    circle.center = circle.center + delta.unit() * (overlap);
    // Debugging information
    std::cout << "Collision detected: " << std::endl;
    std::cout << "Circle 1 center: (" << this->center.x << ", " << this->center.y << ")" << std::endl;
    std::cout << "Circle 2 center: (" << circle.center.x << ", " << circle.center.y << ")" << std::endl;
    std::cout << "overlap: " << overlap << std::endl;
}

void System::addRigidBody2DCircle(double radius, double mass, Vector center, Vector velocity){
  if (std::find_if(this->circles.begin(),this->circles.end() ,[&center](RigidBody2DCircle& circle){
               return center == circle.center;
               }) != this->circles.end()) return;
  this->circles.push_back(RigidBody2DCircle(radius,mass,center,velocity,this->gAcceleration * mass));
}

void System::constraints(RigidBody2DCircle &circle){
  if(circle.center.x - circle.radius < 0){
    circle.center.x = 0 + circle.radius;
  }
  else if(circle.center.x + circle.radius > dimensions.x){
    circle.center.x = dimensions.x - circle.radius;
  }
  if(circle.center.y - circle.radius < 0){
    circle.center.y = 0 + circle.radius;
  }
  else if(circle.center.y + circle.radius > dimensions.y){
    circle.center.y = dimensions.y - circle.radius;
  }
}

void System::propogate(double d_t) {
    if (this->circles.empty()) return;

for(int sim_num = 1; sim_num <= 100; sim_num++){
    for (auto &circle : this->circles) {
        this->constraints(circle);
    }
    for (int i = 0; i < this->circles.size(); ++i) {
        for (int j = i + 1; j < this->circles.size(); ++j) {
            if (this->circles[i].center.distance(this->circles[j].center) < this->circles[i].radius + this->circles[j].radius) {
                this->circles[i].collide(this->circles[j]);
            }
        }
    }
    }

    for (auto &circle : this->circles) {
        // Update velocity
        circle.velocity = (circle.center - circle.center_prev);

        Vector acceleration = std::accumulate(circle.forces.begin(), circle.forces.end(), Vector(0.0, 0.0)) / circle.mass;
        Vector center_new = circle.center + circle.velocity + acceleration * d_t * d_t;
        circle.center_prev = circle.center;
        circle.center = center_new;

    }
}
