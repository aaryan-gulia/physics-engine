
#include <vector>

namespace physics2D{
  
class Vector{
  public: 
    double x,y;

  public:
    Vector(double x, double y):x(x),y(y){};
    Vector operator+(Vector vec);
    Vector operator-(Vector vec);
    Vector operator*(double scalar);
    Vector operator/(double scalar);    
    double distance(Vector vec1);
    double length();
};

class RigidBody2DCircle{
  const double circumfrence, mass;
  Vector center;
  Vector velocity;
  std::vector<Vector> forces;

  public:
    RigidBody2DCircle(double circumfrence, double mass, Vector center, Vector velocity):
    circumfrence(circumfrence), mass(mass), center(center), velocity(velocity){};
};

class System{
  Vector dimensions;
  std::vector<RigidBody2DCircle> circles;

  public:
    System();
    void addRigidBody2DCircle(double circumfrence, double mass, Vector center, Vector velocity);
    void propogate(double d_t);
};

}
