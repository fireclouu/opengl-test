#ifndef OPENGL_UTILS_HPP
#define OPENGL_UTILS_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

extern int success;
extern char infoLog[512];
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int window_init(GLFWwindow** window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);
GLuint compile_shader(const char* shaderSource, const int shaderType);

#endif
