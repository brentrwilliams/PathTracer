/**
 * PathTracer.cpp
 * 
 * @author Brent Williams brent.robert.williams@gmail.com
 */ 

#include "PathTracer.hpp"

int main(int argc, char const *argv[])
{
   unsigned int imageWidth = 500;
   unsigned int imageHeight = 500;
   float halfWidth = float(imageWidth) / 2.0f;
   float halfHeight = float(imageHeight) / 2.0f;
   
   Image image(imageWidth, imageHeight);
   Sphere sphere(vec3(0,0,0), 100.0f);

   for (unsigned int x = 0; x < imageWidth; x++)
   {
      for (unsigned int y = 0; y < imageHeight; y++)
      {
         vec3 color(1,1,1);
         float t = 0.0f;

         // Orthographic Projection
         vec3 position(float(x) - halfWidth, float(y) - halfHeight, -1000);
         vec3 direction(0, 0, 1);
         Ray ray(position, direction);

         if (sphere.intersect(ray, t))
         {
            image.setColor(x,y, color);
         }
      }
   }   

   image.writeTGA("out.tga");

   return 0;
}