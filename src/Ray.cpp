/**
 * Ray.cpp
 * 
 * @author Brent Williams brent.robert.williams@gmail.com
 */ 

#include "Ray.hpp"

Ray::Ray(const glm::vec3& position, const glm::vec3& direction)
{
   this->position = position;
   this->direction = glm::normalize(direction);
}

Ray::~Ray()
{
   
}