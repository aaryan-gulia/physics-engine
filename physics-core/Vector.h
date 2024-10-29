


namespace physics_type{
  
class Vector2{
  public: 
    float x,y;

  public:
    Vector2() = default;
    Vector2(double x, double y):x(x),y(y){};
    Vector2 const operator+(Vector2 vec);
    Vector2 operator-(Vector2 vec);
    void operator+=(Vector2 vec);
    void operator-=(Vector2 vec);
    bool const operator==(Vector2 vec);
    Vector2 operator*(double scalar);
    Vector2 operator/(double scalar);    
    float distance(Vector2 vec1);
    float distance_squared(Vector2 vec1);
    float length_squared();
    float length();
    Vector2 unit();
};

}  
