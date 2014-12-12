/**
 * PatheTracer.hpp
 * 
 * @author Brent Williams brent.robert.williams@gmail.com
 */ 

#ifndef PATH_TRACER_HPP
#define PATH_TRACER_HPP

#include <glm/glm.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream> 

#include "Ray.hpp"
#include "Sphere.hpp"
#include "Image.hpp"
#include "PhongMaterial.hpp"

using namespace std;

class PathTracer
{
public:
   unsigned int imageWidth;
   unsigned int imageHeight;
   Image image;

   PathTracer(unsigned int width, unsigned int height);
   PathTracer(unsigned int width, unsigned int height, glm::vec3 fillColor);
   ~PathTracer();
   void trace();
   void writeImage(const char *imageName);
};


#endif