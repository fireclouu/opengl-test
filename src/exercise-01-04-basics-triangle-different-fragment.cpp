#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
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
  // left triangle
  const float verticesTriangleLeft[] = {
    -0.5f,  0.5f,  0.0f,
    -1.0f, -0.5f,  0.0f,
     0.0f, -0.5f,  0.0f,
  };

  // right triangle
  const float verticesTriangleRight[] = {
     0.0f, -0.5f,  0.0f,
     0.5f,  0.5f,  0.0f,
     1.0f, -0.5f,  0.0f,
  };

  const char* vertexShaderFilePath = "shaders/vertex_shader.glsl";
  const char* fragmentShaderFilePathOrange = "shaders/fragment_shader.glsl";
  const char* fragmentShaderFilePathPurple = "shaders/fragment_shader_purple.glsl";

  GLuint VAOs[2];
  GLuint VBOs[2];
  glGenVertexArrays(2, VAOs);
  glGenBuffers(2, VBOs);

  // left triangle configurations
  glBindVertexArray(VAOs[0]);
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTriangleLeft), verticesTriangleLeft, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // right triangle configurations
  glBindVertexArray(VAOs[1]);
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTriangleRight), verticesTriangleRight, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  const char* vertexShaderSource = readFileToCharPointer(vertexShaderFilePath);
  const char* fragmentShaderSourcePurple = readFileToCharPointer(fragmentShaderFilePathPurple);
  const char* fragmentShaderSourceOrange = readFileToCharPointer(fragmentShaderFilePathOrange);

  GLuint vertexShader;
  GLuint fragmentShaderPurple;
  GLuint fragmentShaderOrange;

  try {
    vertexShader = compile_shader(vertexShaderSource, GL_VERTEX_SHADER);
    fragmentShaderPurple = compile_shader(fragmentShaderSourcePurple, GL_FRAGMENT_SHADER);
    fragmentShaderOrange = compile_shader(fragmentShaderSourceOrange, GL_FRAGMENT_SHADER);
  } catch (const std::runtime_error& e) {
    std::cout << "An error occured. " << e.what() << "\n";
    return -1;
  }
  
  GLuint shaderProgramFragPurple = glCreateProgram();
  GLuint shaderProgramFragOrange = glCreateProgram();

  // program configs with Purple frag color //
  glAttachShader(shaderProgramFragPurple, vertexShader);
  glAttachShader(shaderProgramFragPurple, fragmentShaderPurple);
  glLinkProgram(shaderProgramFragPurple);

  // status checking
  glGetProgramiv(shaderProgramFragPurple, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgramFragPurple, 512, NULL, infoLog);
    throw std::runtime_error("Error linking shaders: " + (std::string) infoLog + "\n");
  }

  // program configs with Orange frag color //
  glAttachShader(shaderProgramFragOrange, vertexShader);
  glAttachShader(shaderProgramFragOrange, fragmentShaderOrange);
  glLinkProgram(shaderProgramFragOrange);

  // status checking
  glGetProgramiv(shaderProgramFragOrange, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgramFragOrange, 512, NULL, infoLog);
    throw std::runtime_error("Error linking shaders: " + (std::string) infoLog + "\n");
  }

  // free memory used after successful link
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShaderPurple);
  glDeleteShader(fragmentShaderOrange);

  while (!glfwWindowShouldClose(window)) {
    process_input(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // left triangle render
    glUseProgram(shaderProgramFragPurple);
    glBindVertexArray(VAOs[0]);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(verticesTriangleLeft) / 3);
    glBindVertexArray(0);

    // right triangle render
    glUseProgram(shaderProgramFragOrange);
    glBindVertexArray(VAOs[1]);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(verticesTriangleRight) / 3);
    glBindVertexArray(0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  
  return 0;
}
