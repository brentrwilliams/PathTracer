/**
 * PatheTracer.hpp
 * 
 * @author Brent Williams brent.robert.williams@gmail.com
 */ 

#ifndef PATH_TRACER_HPP
#define PATH_TRACER_HPP

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream> 
#include <time.h>

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
   unsigned int traceCount;
   glm::vec3 fillColor;

   PathTracer(unsigned int width, unsigned int height);
   PathTracer(unsigned int width, unsigned int height, glm::vec3 fillColor);
   ~PathTracer();
   void trace();
   void writeImage(const char *imageName);
   GLuint getOpenGLTexture();
   void updateOpenGLTexture(GLuint textureID);
   void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

};


#endif