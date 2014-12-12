/**
 * PathTracer.cpp
 * 
 * @author Brent Williams brent.robert.williams@gmail.com
 */ 

#include "PathTracer.hpp"

PathTracer::PathTracer(unsigned int width, unsigned int height) :image(width,height)
{
   this->imageWidth = width;
   this->imageHeight = height;
}

PathTracer::~PathTracer()
{

}

void PathTracer::trace()
{
   float halfWidth = float(imageWidth) / 2.0f;
   float halfHeight = float(imageHeight) / 2.0f;
   Sphere sphere(vec3(0,0,0), 100.0f);

   glm::vec3 ka(0,0.1,0);
   glm::vec3 kd(0,0.4,0);
   glm::vec3 ks(0.5,0.5,0.5);
   float ns = 20.0;
   PhongMaterial phongMat(ka,kd,ks,ns);

   for (unsigned int x = 0; x < imageWidth; x++)
   {
      for (unsigned int y = 0; y < imageHeight; y++)
      {
         float t = 0.0f;

         // Orthographic Projection
         vec3 position(float(x) - halfWidth, float(y) - halfHeight, -1000);
         vec3 direction(0, 0, 1);
         Ray ray(position, direction);

         if (sphere.intersect(ray, t))
         {
            glm::vec3 hitPosition = ray.position + (t * ray.direction);
            glm::vec3 normal = sphere.getNormal(hitPosition);

            //cout << "(" << x << ", " << y << ")\n";
            vec3 color = phongMat.calculateSurfaceColor(ray, hitPosition, normal);
            image.setColor(x,y, color);
         }
      }
   }   

}