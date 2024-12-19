#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "external/stb/stb_image.h"

int main(int argc, char** argv) {
  std::cout << "STB Version: " << STBI_VERSION << std::endl;
  return 0;
}
