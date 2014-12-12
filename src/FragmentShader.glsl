#version 400

// Interpolated values from the vertex shaders
smooth in vec2 uv;

out vec4 frag_colour;


void main () 
{
   frag_colour = vec4 (uv.x, uv.y, 0.0, 1.0);
}