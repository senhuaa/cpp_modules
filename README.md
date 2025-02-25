# cpp_modules

This project demonstrates the use of C++20 modules with external dependencies like SDL and ENTT.

## Building the Project
To build the project, you need to have a compatible compiler that supports C++20 modules. **Only MSVC is supported** due to limitations with MinGW and its lack of full C++20 modules support.

### Requirements

- **MSVC (Microsoft Visual C++)** compiler is required.
- CMake 3.30 or higher.
- SDL3 (included in the project).
- ENTT (included in the project).

### Steps
1. Clone the repository.
2. Navigate to the project directory.
3. Create a build directory:
```bash
mkdir build
cd build
cmake -G Ninja ..
ninja
```
