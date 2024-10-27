
#include <vector>

namespace physics2D{
  
class Vector{
  public: 
    double x,y;

  public:
    Vector(double x, double y):x(x),y(y){};
    Vector operator+(Vector vec);
    Vector operator-(Vector vec);
    bool const operator==(Vector vec);
    Vector operator*(double scalar);
    Vector operator/(double scalar);    
    double distance(Vector vec1);
    double length();
    Vector unit();
};

class RigidBody2DCircle{
  public: 
    const double radius, mass;
    Vector center;
    Vector center_prev;
    Vector velocity;
    std::vector<Vector> forces;

  public:
    RigidBody2DCircle(double radius, double mass, Vector center, Vector velocity, Vector gravity);
    void collide(RigidBody2DCircle &circle);
};

class System{
  public: 
  Vector dimensions;
  Vector gAcceleration;
  std::vector<RigidBody2DCircle> circles;

  public:
    System(Vector dimensions, Vector gAcceleration):dimensions(dimensions),gAcceleration(gAcceleration){};
    void addRigidBody2DCircle(double radius, double mass, Vector center, Vector velocity);
    void propogate(double d_t);
    void constraints(RigidBody2DCircle &circle);
};

}
