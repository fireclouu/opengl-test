#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readFile(const char *filePath) {
  FILE *file = fopen(filePath, "r");
  if (!file) {
    fprintf(stderr, "Could not open file: %s\n", filePath);
    return NULL;
  }
  fseek(file, 0, SEEK_END);
  long length = ftell(file);
  rewind(file);

  char *buffer = (char*) malloc(length + 1);
  if (!buffer) {
    fprintf(stderr, "Memory allocation failed!\n");
    fclose(file);
    return NULL;
  }

  fread(buffer, 1, length, file);
  buffer[length] = '\0';
  fclose(file);
  return buffer;
}
