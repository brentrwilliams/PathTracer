#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>

#include "Image.hpp"
#include "OpenGLShader.hpp"



int main () {
   // start GL context and O/S window using the GLFW helper library
   if (!glfwInit ()) 
   {
      fprintf (stderr, "ERROR: could not start GLFW3\n");
      return 1;
   } 

   unsigned int windowWidth = 512;
   unsigned int windowHeight = 512;

   glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
   glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
   glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

   GLFWwindow* window = glfwCreateWindow (windowWidth, windowHeight, "Path Tracer", NULL, NULL);
   if (!window) 
   {
      fprintf (stderr, "ERROR: could not open window with GLFW3\n");
      glfwTerminate();
      return 1;
   }
   glfwMakeContextCurrent (window);
                                  
   // start GLEW extension handler
   glewExperimental = GL_TRUE;
   glewInit ();

   // tell GL to only draw onto a pixel if the shape is closer to the viewer
   glEnable (GL_DEPTH_TEST); // enable depth-testing
   glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"

   /* OTHER STUFF GOES HERE NEXT */

   GLuint shaderProgram = loadShader("VertexShader.glsl","FragmentShader.glsl");

   GLuint VertexArrayID;
   glGenVertexArrays(1, &VertexArrayID);
   glBindVertexArray(VertexArrayID);

   static const GLfloat g_vertex_buffer_data[] = 
   {
      0.5f,  0.5f,  0.0f,
      0.5f, -0.5f,  0.0f,
      -0.5f, 0.5f,  0.0f, 

      0.5f, -0.5f,  0.0f,
      -0.5f,  -0.5f,  0.0f,
      -0.5f, 0.5f,  0.0f, 
   };

   static const GLfloat g_uv_buffer_data[] =
   {
      1.0f, 1.0f,
      1.0f, 0.0f,
      0.0f, 1.0f,

      1.0f, 0.0f,
      0.0f, 0.0f,
      0.0f, 1.0f,
   };


   GLuint vertexbuffer;
   glGenBuffers(1, &vertexbuffer);
   glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
   glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
   
   GLuint uvbuffer;
   glGenBuffers(1, &uvbuffer);
   glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
   glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

   Image image(windowWidth, windowHeight);

   for (int i = 0; i < windowWidth; i++)
   {
      for (int j = 0; j < windowHeight; j++)
      {
         if (i <= 256 && j <= 256)
         {
            image.setColor(i,j, 1,0,0);
         }
         else if (i > 256 && j <= 256)
         {
            image.setColor(i,j, 0,1,0);
         }
         else if (i <= 256 && j > 256)
         {
            image.setColor(i,j, 0,0,1);
         }
      }
   }

   GLuint texture = image.getOpenGLTexture();

   while (!glfwWindowShouldClose (window)) 
   {
      // wipe the drawing surface clear
      glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glUseProgram (shaderProgram);

      // 1rst attribute buffer : vertices
      glEnableVertexAttribArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
      glVertexAttribPointer(
         0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
         3,                  // size
         GL_FLOAT,           // type
         GL_FALSE,           // normalized?
         0,                  // stride
         (void*)0            // array buffer offset
      );

      // 2nd attribute buffer : UVs
      glEnableVertexAttribArray(1);
      glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
      glVertexAttribPointer(
         1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
         2,                                // size : U+V => 2
         GL_FLOAT,                         // type
         GL_FALSE,                         // normalized?
         0,                                // stride
         (void*)0                          // array buffer offset
      );

      // draw points 0-3 from the currently bound VAO with current in-use shader
      glDrawArrays (GL_TRIANGLES, 0, 6);

      glDisableVertexAttribArray(0);
      glDisableVertexAttribArray(1);

      // update other events like input handling 
      glfwPollEvents ();
      // put the stuff we've been drawing onto the display
      glfwSwapBuffers (window);
   }
   glDeleteBuffers(1, &vertexbuffer);
   glDeleteBuffers(1, &uvbuffer);
   glDeleteProgram(shaderProgram);
   glDeleteVertexArrays(1, &VertexArrayID);
   /* OTHER STUFF ENDS HERE */
  
   // close GL context and any other GLFW resources
   glfwTerminate();
   return 0;
}