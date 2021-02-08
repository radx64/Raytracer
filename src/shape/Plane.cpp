#include "Plane.hpp"

#include <cmath>

namespace rt
{
namespace shape
{

core::Vector Plane::getNormalAt(core::Point& p)
{
    core::Vector normal (getPosition());
    normal.normalize();
    return normal;
}

bool Plane::hit(core::Ray r, double& t)
{
    core::Vector rayDirection = r.getDirection();
    double d = rayDirection.dotProduct(getPosition());

    if (d >= 0) return false;

    /* this 550 value is for testing purpose only (-y delta)*/
    /* plane calcilations are not working right now properly */
    double distance = (getPosition() * r.getOrgin()) * -1.0/d + 300.0; 

    if(distance > 0 && distance < t)
    {
        t = distance;
        return true;
    }
    return false;
}

const core::Vector Plane::UV(const core::Point& p)
{
    return core::Vector{0.0, 0.0, 0.0};
}



}  // namespace shape
}  // namespace rt
