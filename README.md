# TypeScript to Assembly Compiler

This project implements a prrof-of-concept compiler that translates TypeScript code into assembly language.

## Features

- Compile TypeScript code strings to assembly
- Compile TypeScript files to assembly

## Roadmap
- Configurable optimization levels
- Debug information emission
- Cross-platform support (macOS, Linux, Windows)
- Multi-architecture support (AMD64, ARM64)

## Prerequisites

- CMake (version 3.30 or higher)
- Clang++ or GCC with C++20 support
- Make (for Unix-like systems) or Visual Studio (for Windows)

## Building the Project

### Using CMake

1. Clone the repository:
   ```
   git clone https://github.com/yourusername/typescript-compiler.git
   cd typescript-compiler
   ```

2. Configure the project:
   ```
   cmake -S . -B build
   ```

3. Build the project:
   ```
   cmake --build build
   ```

### Using Make

1. Clone the repository:
   ```
   git clone https://github.com/yourusername/typescript-compiler.git
   cd typescript-compiler
   ```

2. Build the project:
   ```
   make
   ```

## Usage

Here's a simple example of how to use the compiler:

```sh
tscompiler <source.ts> -o <output.asm>
```

## Running Tests

To run the test suite:

```
cd build
ctest
```

## License

This project is licensed under the MIT License - see the `LICENSE` file for details.

## Contact

If you have any questions or feedback, please open an issue on the GitHub repository.
