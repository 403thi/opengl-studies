#version 330 core
out vec4 FragColor;
in vec3 customColor;
in vec2 texCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
   //FragColor = vec4(customColor, 1.0f);
   //FragColor = texture(texture1, texCoord) * vec4(customColor, 1.0);
   FragColor = mix(texture(texture1, texCoord), texture(texture2, vec2(texCoord.x, texCoord.y*-1)), 0.2);
}