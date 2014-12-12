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

   image.writeTGA("out.tga");

   return 0;
}