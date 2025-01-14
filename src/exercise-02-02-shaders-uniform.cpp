#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include "utils/file_utils.hpp"
#include "utils/opengl_utils.hpp"

int render();

GLFWwindow* window;

int main()
{
  if (window_init(&window) != 0) return -1;
  int status = render();

  glfwTerminate();
  return status;
}

int render() {
  const float vertices[] = {
    0.0f, 0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f
  };

  const char* vertexShaderFilePath = "shaders/exercise-02-02-shader-vertex.glsl";
  const char* fragmentShaderFilePath = "shaders/exercise-02-02-shader-fragment.glsl";

  GLuint VAO;
  GLuint VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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

  // compilation checks
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    throw std::runtime_error("Error linking shaders: " + (std::string) infoLog + "\n");
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  while(!glfwWindowShouldClose(window)) {
    process_input(window);

    glClearColor(0.1569, 0.1569, 0.1569, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);

    float timeValue = glfwGetTime();
    float blueValue = sin(timeValue) / 2.0f + 0.5f;
    int vertexColorLocation = glGetUniformLocation(shaderProgram, "appColor");
    glUniform4f(vertexColorLocation, 0.0f, 0.0f, blueValue, 1.0f);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / 3);
    glBindVertexArray(0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  return 0;
}
