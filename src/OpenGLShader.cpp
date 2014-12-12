
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

   // ***

   GLint Result = GL_FALSE;
   int InfoLogLength;
   // Create the shaders
   GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
   GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

   // Compile Vertex Shader
   printf("Compiling shader : %s\n", vertexShaderName);
   //char const * VertexSourcePointer = VertexShaderCode.c_str();
   glShaderSource(VertexShaderID, 1, &vertexShaderText , NULL);
   glCompileShader(VertexShaderID);

   // Check Vertex Shader
   glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
   glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
   if ( InfoLogLength > 0 ){
      std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
      glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
      printf("%s\n", &VertexShaderErrorMessage[0]);
   }



   // Compile Fragment Shader
   printf("Compiling shader : %s\n", fragmentShaderName);
   //char const * FragmentSourcePointer = FragmentShaderCode.c_str();
   glShaderSource(FragmentShaderID, 1, &fragmentShaderText , NULL);
   glCompileShader(FragmentShaderID);

   // Check Fragment Shader
   glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
   glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
   if ( InfoLogLength > 0 ){
      std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
      glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
      printf("%s\n", &FragmentShaderErrorMessage[0]);
   }



   // Link the program
   printf("Linking program\n");
   GLuint ProgramID = glCreateProgram();
   glAttachShader(ProgramID, VertexShaderID);
   glAttachShader(ProgramID, FragmentShaderID);
   glLinkProgram(ProgramID);

   // Check the program
   glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
   glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
   if ( InfoLogLength > 0 ){
      std::vector<char> ProgramErrorMessage(InfoLogLength+1);
      glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
      printf("%s\n", &ProgramErrorMessage[0]);
   }

   glDeleteShader(VertexShaderID);
   glDeleteShader(FragmentShaderID);

   return ProgramID;

   // ***

   // GLuint vertexShader = glCreateShader (GL_VERTEX_SHADER);
   // glShaderSource(vertexShader, 1, &vertexShaderText, NULL);
   // glCompileShader(vertexShader);

   // GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
   // glShaderSource(fragmentShader, 1, &fragmentShaderText, NULL);
   // glCompileShader(fragmentShader);

   // GLuint shaderProgram = glCreateProgram ();
   // glAttachShader(shaderProgram, fragmentShader);
   // glAttachShader(shaderProgram, vertexShader);
   // glLinkProgram(shaderProgram);

   // return shaderProgram;
}