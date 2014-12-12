#include "GLFWTest.hpp"

void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
   PathTracer* pathTracer = reinterpret_cast<PathTracer *>(glfwGetWindowUserPointer(window));
   pathTracer->keyboardCallback(window, key, scancode, action, mods);
}

int main (int argc, char const *argv[])
{
   // start GL context and O/S window using the GLFW helper library
   if (!glfwInit ()) 
   {
      fprintf (stderr, "ERROR: could not start GLFW3\n");
      return 1;
   }

   unsigned int width = 640;
   unsigned int height = 480;

   if (argc == 3)
   {
      width = atoi(argv[1]);
      width = atoi(argv[2]);
   }

   glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
   glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
   glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

   GLFWwindow* window = glfwCreateWindow (width, height, "Path Tracer", NULL, NULL);
   if (!window) 
   {
      fprintf (stderr, "ERROR: could not open window with GLFW3\n");
      glfwTerminate();
      return 1;
   }
   glfwMakeContextCurrent (window);
   glfwSetKeyCallback(window, keyboardCallback);
                                  
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
      1.0f,  1.0f,  0.0f,
      1.0f, -1.0f,  0.0f,
      -1.0f, 1.0f,  0.0f, 

      1.0f, -1.0f,  0.0f,
      -1.0f,  -1.0f,  0.0f,
      -1.0f, 1.0f,  0.0f, 
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


   glm::vec3 fillColor(169.0f/255.0f, 213.0f/255.0f, 235.0f/255.0f);
   PathTracer pathTracer(width, height, fillColor);

   // Pass the window a pointer to the path tracer so we can access its variables in callbacks
   glfwSetWindowUserPointer(window, &pathTracer);

   GLuint texture = pathTracer.getOpenGLTexture();
   
   // Get a handle for our "myTextureSampler" uniform
   GLuint TextureID  = glGetUniformLocation(shaderProgram, "myTextureSampler");

   while (!glfwWindowShouldClose (window)) 
   {
      pathTracer.trace();
      pathTracer.updateOpenGLTexture(texture);

      // wipe the drawing surface clear
      glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glUseProgram (shaderProgram);

      // Bind our texture in Texture Unit 0
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, texture);
      // Set our "myTextureSampler" sampler to use Texture Unit 0
      glUniform1i(TextureID, 0);

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
   glDeleteTextures(1, &TextureID);
   glDeleteVertexArrays(1, &VertexArrayID);
   /* OTHER STUFF ENDS HERE */
  
   // close GL context and any other GLFW resources
   glfwTerminate();
   return 0;
}