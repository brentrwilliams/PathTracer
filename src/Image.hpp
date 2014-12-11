/**
 * Image.hpp
 * 
 * @author Brent Williams brent.robert.williams@gmail.com
 */ 

#ifndef IMAGE_H
#define IMAGE_H

#include <glm/glm.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream> 

using namespace glm; 
using namespace std;

typedef struct {
   char  idlength;
   char  colourmaptype;
   char  datatypecode;
   short int colourmaporigin;
   short int colourmaplength;
   char  colourmapdepth;
   short int x_origin;
   short int y_origin;
   short width;
   short height;
   char  bitsperpixel;
   char  imagedescriptor;
} TGAHeader;

class Image 
{
   public:
      float *r;
      float *g;
      float *b;
      int width;
      int height;
      char filename[256];
      
      Image();
      Image(int width, int height);
      ~Image();
      unsigned int index2D(unsigned int x, unsigned int y);
      void allocateImage(int width, int height);
      void readTGA(const char *filename);
      void writeTGA(const char *filename);
      void scaleColors();
      vec3 getColor(int x, int y);   
      void setColor(int x, int y, float newR, float newG, float newB);
      void setColor(int x, int y, const vec3& color);
};

#endif