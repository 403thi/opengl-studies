#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform vec2 position;
out vec3 customColor;
out vec2 texCoord;

uniform mat4 transform;

void main()
{
   // gl_Position = vec4(aPos.xy + position.xy, aPos.z, 1.0f);
   gl_Position = transform * vec4(aPos, 1.0f);
   customColor = aColor * vec3(position.xy + vec2(0.4f, 0.4f), 0.0f);
   texCoord = aTexCoord;
};