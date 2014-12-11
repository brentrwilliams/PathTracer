
#include "OpenGLShader.hpp"
using namespace std;

GLuint loadShader(const char* vertexShaderName, const char* fragmentShaderName)
{
   string line;
   ifstream vertexShaderFile(vertexShaderName);
   if (!vertexShaderFile.is_open())
   {
      cerr << "ERROR: Unable to open file \"" << vertexShaderName << "\"" << endl; 
      return 0;
   }

   string vertexShaderString;
   while (getline(vertexShaderFile,line))
   {
      vertexShaderString += line + '\n';
   }
   const char* vertexShaderText = vertexShaderString.c_str();
   vertexShaderFile.close();
   
   ifstream fragmentShaderFile(fragmentShaderName);
   if (!fragmentShaderFile.is_open())
   {
      cerr << "ERROR: Unable to open file \"" << fragmentShaderName << "\"" << endl; 
      return 0;
   }

   string fragmentShaderString;
   while (getline(fragmentShaderFile,line))
   {
      fragmentShaderString += line + '\n';
   }
   const char* fragmentShaderText = fragmentShaderString.c_str();
   fragmentShaderFile.close();

   GLuint vertexShader = glCreateShader (GL_VERTEX_SHADER);
   glShaderSource(vertexShader, 1, &vertexShaderText, NULL);
   glCompileShader(vertexShader);

   GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(fragmentShader, 1, &fragmentShaderText, NULL);
   glCompileShader(fragmentShader);

   GLuint shaderProgram = glCreateProgram ();
   glAttachShader(shaderProgram, fragmentShader);
   glAttachShader(shaderProgram, vertexShader);
   glLinkProgram(shaderProgram);

   return shaderProgram;
}