#ifndef OPENGL_SHADER_HPP
#define OPENGL_SHADER_HPP

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 

GLuint loadShader(const char* vertexShaderName, const char* fragmentShaderName);

#endif