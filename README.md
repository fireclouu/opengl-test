# OpenGL Test
Learning Graphics Render Programming via OpenGL API, to utilize GPU hardware for cross-device support.

## Motivation
For future development integration which requires custom or uniform UI across devices that understands OpenGL API.

## How to run
Make sure your system has GUI or running desktop environment, and understands core OpenGL 3.3.

Install required libraries:
```bash
sudo apt-get install clang cmake make libglfw3 libglfw3-dev
```

This project also uses GLAD library which is already implemented. No need to reconfigure for *linux-based* systems.

Clone this repository
```bash
git clone https://github.com/fireclouu/opengl-test.git
```

After cloning is complete, execute:
```bash
cd opengl-test/
chmod +x run.sh
```

After mode changing, execute build process by running:
```bash
./run.sh
```

This build script automates nearly everything in project. CMake seeks all `exercise-*.cpp` source files available in `src/`, copy new/modified shader files into `build/bin/shaders` and makes binaries inside `build/bin`.

For convenience, the script has UI that allows to execute binaries instantly, user can pick binaries to execute, listed in reversed order.

> [!NOTE]
> First build may take time due to caching. Subsequent builds after first one will execute much faster

## Milestones
- [x] Introduction to Graphics Programming
- [x] OpenGL as Graphics API
- [x] Basic Rendering Setup
- [x] VAOs, VBOs, EBO
- [x] Shaders

## Resources
- [https://learnopengl.com](https://learnopengl.com/)
- [http://www.opengl-tutorial.org](http://www.opengl-tutorial.org/)
