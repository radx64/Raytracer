#include "Color.hpp"

namespace rt
{
namespace core
{

    Color Color::operator + (const Color& c)
    {
    	return Color{red+c.red, green+c.green, blue+c.blue};
    }

    Color Color::operator + (const double& inc)
    {
    	return Color{red+inc, green+inc, blue+inc};
    }

    Color Color::operator - (const Color& c)
    {
    	return Color{red-c.red, green-c.green, blue-c.blue};
    }

    Color Color::operator * (const double& mult)
    {
    	return Color{red*mult, green*mult, blue*mult};
    }

    Color Color::operator * (const Color& rhs)
    {
    	return Color{red*rhs.red, green*rhs.green, blue*rhs.blue};
    }

}  // namesapce core
}  // namespace rt