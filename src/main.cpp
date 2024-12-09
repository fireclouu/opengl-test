#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "opengl_utils.hpp"
#include "file_utils.hpp"

// render int VBOTriangle1();
int VBOTriangle2();
int moreVboAndVao();
int EBORectangle();
int TriangleExercise1();

GLFWwindow* window;

int main()
{
  if (window_init(window) != 0) return -1;
  int status = TriangleExercise1();
  // int status = EBORectangle();

  // glfw: terminate, clearing all previously allocated GLFW resources.
  // ------------------------------------------------------------------
  glfwTerminate();
  return status;
}

int VBOTriangle(const float vertices[], const size_t vertSize) {
  const char* vertexShaderFilePath = "shaders/vertex_shader.glsl";
  const char* fragmentShaderFilePath = "shaders/fragment_shader.glsl";

  GLuint VAO;
  GLuint VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertSize, vertices, GL_STATIC_DRAW);

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

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLES, 0, vertSize / 3);

    glBindVertexArray(0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  return 0;
}

int TriangleExercise1() {
  const float vertices1[] = {
    // left triangle
    -0.5f, 0.5f, 0.0f,
    -1.0f, -0.5f, 0.0f,
    0.0f, -0.5f, 0.0f,
  };

  const float vertices2[] = {
    // right triangle
    0.0f, -0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
    1.0f, -0.5f, 0.0f,
  };

  const char* vertexShaderFilePath = "shaders/vertex_shader.glsl";
  const char* fragmentShaderFilePath1 = "shaders/fragment_shader.glsl";
  const char* fragmentShaderFilePath2 = "shaders/fragment_shader_1.glsl";

  GLuint VAO[2];
  GLuint VBO[2];
  glGenVertexArrays(2, VAO);
  glGenBuffers(2, VBO);

  // left triangle
  glBindVertexArray(VAO[0]);
  glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // right triangle
  glBindVertexArray(VAO[1]);
  glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  const char* vertexShaderSource = readFileToCharPointer(vertexShaderFilePath);
  const char* fragmentShaderSource1 = readFileToCharPointer(fragmentShaderFilePath1);
  const char* fragmentShaderSource2 = readFileToCharPointer(fragmentShaderFilePath2);

  GLuint vertexShader;
  GLuint fragmentShader1;
  GLuint fragmentShader2;

  try {
    vertexShader = compile_shader(vertexShaderSource, GL_VERTEX_SHADER);
    fragmentShader1 = compile_shader(fragmentShaderSource1, GL_FRAGMENT_SHADER);
    fragmentShader2 = compile_shader(fragmentShaderSource2, GL_FRAGMENT_SHADER);
  } catch (const std::runtime_error& e) {
    std::cout << "An error occured. " << e.what() << "\n";
    return -1;
  }

  GLuint shaderProgram1 = glCreateProgram();
  GLuint shaderProgram2 = glCreateProgram();

  // left triangle shader prog
  glAttachShader(shaderProgram1, vertexShader);
  glAttachShader(shaderProgram1, fragmentShader1);
  glLinkProgram(shaderProgram1);

  // compilation checks
  glGetProgramiv(shaderProgram1, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram1, 512, NULL, infoLog);
    throw std::runtime_error("Error linking shaders: " + (std::string) infoLog + "\n");
  }

  // right triangle shader prog
  glAttachShader(shaderProgram2, vertexShader);
  glAttachShader(shaderProgram2, fragmentShader2);
  glLinkProgram(shaderProgram2);

  // compilation checks
  glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram2, 512, NULL, infoLog);
    throw std::runtime_error("Error linking shaders: " + (std::string) infoLog + "\n");
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader1);
  glDeleteShader(fragmentShader2);

  while(!glfwWindowShouldClose(window)) {
    process_input(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    process_input(window);
    // left triangle draws
    glUseProgram(shaderProgram1);
    glBindVertexArray(VAO[0]);

    glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices1) / 3);

    glBindVertexArray(0);

    // right triangle draws
    glUseProgram(shaderProgram2);
    glBindVertexArray(VAO[1]);

    glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices2) / 3);

    glBindVertexArray(0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  return 0;
}

int VBOTriangle1() {
  const float vertices[] = {
    0.0f, 0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f
  };

  return VBOTriangle(vertices, sizeof(vertices));
}

int VBOTriangle2() {
  const float vertices[] = {
    // left triangle
    -0.5f, 0.5f, 0.0f,
    -1.0f, -0.5f, 0.0f,
    0.0f, -0.5f, 0.0f,

    // right triangle
    0.0f, -0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
    1.0f, -0.5f, 0.0f,
  };

  return VBOTriangle(vertices, sizeof(vertices));
}

int EBORectangle() {
  const char* vertexShaderFilePath = "shaders/vertex_shader.glsl";
  const char* fragmentShaderFilePath = "shaders/fragment_shader.glsl";

  // optimized vertex draw using EBO
  const float vertices[] = {
     0.5f,  0.5f,  0.0f,
     0.5f, -0.5f,  0.0f,
    -0.5f,  0.5f,  0.0f,
    -0.5f, -0.5f,  0.0f,
  };

  const int indices[] = {
    0, 1, 2, // first triangle vertices position
    3, 1, 2, // second triangle vertices positions
  };

  // opengl initialization
  GLuint VAO;
  GLuint VBO;
  GLuint EBO;
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

  // shader inits and compilation

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

  // render loop
  // -----------
  while (!glfwWindowShouldClose(window))
  {
    // input
    // -----
    process_input(window);

    // render
    // ------
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);

    // vertices method for drawing
    // glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / 3);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // indexed drawing via EBO
    glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);

    // to unbind, use address of 0
    glBindVertexArray(0);
    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  return 0;
}
