#include "Vector2D.h"


Origin2D_ Origin2D;


Vector2D& Vector2D::Rotate(float angle)
{
    float s = sinf(angle);
    float c = cosf(angle);
    
    float nx = c * x - s * y;
    float ny = s * x + c * y;
    
    x = nx;
    y = ny;
    
    return (*this);
}