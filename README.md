# OpenGL Test
Learning Graphics Render Programming via OpenGL API, to utilize GPU hardware for cross-device support.

## Motivation
For future development integration which requires custom or uniform UI across devices that understands OpenGL API.

## How to run
Make sure your system has GUI or running desktop environment, and understands OpenGL 3.3 installed.

Install required libraries:
```bash
sudo apt-get install clang cmake make libglfw3 libglfw3-dev
```

This project also uses GLAD library which is already used. No need to reconfigure for `linux-based` systems.

Clone this repository, and then execute:
```bash
cd opengl-test/
chmod +x run.sh
```

After mode changing, execute build process by running:
`./run.sh`

This will start making binaries on `opengl-test/build/bin`.

> [!NOTE]
> First build may take more time. Subsequent builds after first one will be much more faster

## Milestones
- [x] Introduction to Graphics Programming
- [x] OpenGL as Graphics API
- [x] Basic Rendering Setup
- [x] VAOs, VBOs, EBO
- [ ] Shaders
## Resources
- [https://learnopengl.com](https://learnopengl.com/)
- [http://www.opengl-tutorial.org](http://www.opengl-tutorial.org/)
