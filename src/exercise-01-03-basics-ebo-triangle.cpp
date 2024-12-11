#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "utils/file_utils.hpp"
#include "utils/opengl_utils.hpp"

// render
int eboRectangle();

GLFWwindow* window;

int main()
{
  if (window_init(&window) != 0) return -1;
  int status = eboRectangle();

  glfwTerminate();
  return status;
}

int eboRectangle() {
  const char* vertexShaderFilePath = "shaders/vertex_shader.glsl";
  const char* fragmentShaderFilePath = "shaders/fragment_shader.glsl";

  const float vertices[] = {
    0.5f,  0.5f,  0.0f,
    0.5f, -0.5f,  0.0f,
   -0.5f,  0.5f,  0.0f,
   -0.5f, -0.5f,  0.0f
  };

  const int indices[] = {
    0, 1, 2,
    3, 1, 2
  };

  GLuint VAO, VBO, EBO;
  glGenBuffers(1, &VBO);
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  const char* vertexShaderSource = readFileToCharPointer(vertexShaderFilePath);
  const char* fragmentShaderSource = readFileToCharPointer(fragmentShaderFilePath);

  GLuint vertexShader;
  GLuint fragmentShader;

  try {
    vertexShader = compile_shader(vertexShaderSource, GL_VERTEX_SHADER);
    fragmentShader = compile_shader(fragmentShaderSource, GL_FRAGMENT_SHADER);
  } catch (const std::runtime_error& e) {
    std::cout << "An error occured. " << e.what() << "\n";
    return -1;
  }

  GLuint shaderProgram = glCreateProgram();

  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    throw std::runtime_error("Error linking shaders: " + (std::string) infoLog + "\n");
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  while(!glfwWindowShouldClose(window)) {
    process_input(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  return 0;
}
