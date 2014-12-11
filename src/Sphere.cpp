/**
 * Sphere.cpp
 * 
 * @author Brent Williams brent.robert.williams@gmail.com
 */ 

#include "Sphere.hpp"

Sphere::Sphere(const glm::vec3& position, float radius)
{
   this->position = position;
   this->radius = radius;
}

Sphere::~Sphere()
{
   
}

bool Sphere::intersect(const Ray& ray, float& t)
{
   float rayDirectionLength = glm::length(ray.direction);
   glm::vec3 displacement = ray.position - position;
   float displacementLength = glm::length(displacement);

   float a = rayDirectionLength * rayDirectionLength;
   float b = 2.0f * glm::dot(ray.direction, displacement);
   float c = (displacementLength * displacementLength) - radius*radius;
   float radicand = b*b - 4.0*a*c;

   if (radicand < 0)
   {
      return false;
   }

   float root = sqrt(radicand);
   float denom = 2.0 * a;
   float t1 = (-b + root) / denom;
   float t2 = (-b - root) / denom;
   bool returnValue = false;

   if (t1 > EPSILON && t2 > EPSILON)
   {
      t = (t1 < t2) ? t1 : t2;
      returnValue = true;
   }
   else if (t1 > EPSILON)
   {
      t = t1;
      returnValue = true;
   }
   else if (t2 > EPSILON)
   {
      t = t2;
      returnValue = true;
   }

   return returnValue;
}