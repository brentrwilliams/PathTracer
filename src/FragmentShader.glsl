#version 400

// Interpolated values from the vertex shaders
smooth in vec2 uv;

// Output values
out vec4 frag_colour;

// Values that stay constant
uniform sampler2D myTextureSampler;

void main () 
{
   //frag_colour = vec4 (uv.x, 1.0-uv.y, 0.0, 1.0);
   frag_colour = texture( myTextureSampler, uv );
}