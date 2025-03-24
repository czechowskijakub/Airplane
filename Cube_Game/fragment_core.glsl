#version 440

out vec4 FragColor;                                 // color of a pixel

in vec3 ourColor;                                   // take color from vertex shader


void main() {
    FragColor = vec4(ourColor, 1.f);
};