/**
 * Sphere.hpp
 * 
 * @author Brent Williams brent.robert.williams@gmail.com
 */ 

#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <glm/glm.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream> 
#include <math.h>

#include "Ray.hpp"

using namespace std;

#define EPSILON 1.0e-6

class Sphere
{
   public:
      glm::vec3 position;
      float radius;
      Sphere(const glm::vec3& position, float radius);
      ~Sphere();
      bool intersect(const Ray& ray, float& t);
};


#endif