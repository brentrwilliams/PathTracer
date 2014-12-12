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
   this->fillColor = glm::vec3(0,0,0);
   traceCount = 0;
   srand(time(NULL));
}

PathTracer::PathTracer(unsigned int width, unsigned int height, glm::vec3 fillColor) :image(width,height)
{
   this->imageWidth = width;
   this->imageHeight = height;
   this->fillColor = fillColor;
   traceCount = 0;
   srand(time(NULL));
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
         float jitterX = ((float) (rand())) / ((float)RAND_MAX);
         float jitterY = ((float) (rand())) / ((float)RAND_MAX);
         vec3 position(float(x) - halfWidth + jitterX, float(y) - halfHeight + jitterY, -1000);
         vec3 direction(0, 0, 1);
         Ray ray(position, direction);

         if (sphere.intersect(ray, t))
         {
            glm::vec3 hitPosition = ray.position + (t * ray.direction);
            glm::vec3 normal = sphere.getNormal(hitPosition);

            //cout << "(" << x << ", " << y << ")\n";
            vec3 color = phongMat.calculateSurfaceColor(ray, hitPosition, normal);
            image.addColor(x,y, color);
         }
         else
         {
            image.addColor(x,y, fillColor);
         }
      }
   }   

   traceCount++;
}

void PathTracer::writeImage(const char* imageName)
{
   if (traceCount == 0)
   {
      image.writeTGA(imageName);
   }
   image.writeTGA(imageName, traceCount);
}

GLuint PathTracer::getOpenGLTexture()
{
   if (traceCount == 0)
   {
      return image.getOpenGLTexture();
   }
   return image.getOpenGLTexture(traceCount);
}

void PathTracer::updateOpenGLTexture(GLuint textureID)
{
   if (traceCount == 0)
   {
      return image.updateOpenGLTexture(textureID);
   }
   return image.updateOpenGLTexture(textureID, traceCount);
}

// Probably suscpetible to race conditions...
void PathTracer::keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
   if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
   {
      writeImage("out.tga");
   }
}