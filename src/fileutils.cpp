#include <fstream>
#include <ios>
#include <stdexcept>
#include <string>

char* readFileToCharPointer(const std::string &filePath) {
  std::ifstream file(filePath, std::ios::binary | std::ios::ate);
  if (!file.is_open()) {
    throw std::runtime_error("Failed to open file: " + filePath);
  }

  std::streamsize size = file.tellg();
  file.seekg(0, std::ios::beg);

  char* buffer = new char[size + 1];

  if (!file.read(buffer, size)) {
    delete[] buffer;
    throw std::runtime_error("Failed to open file: " + filePath);
  }

  buffer[size] = '\0';
  return buffer;
}
