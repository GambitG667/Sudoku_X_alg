# Указываем минимальную версию CMake
cmake_minimum_required(VERSION 3.10)

# Имя проекта
project(SudokuProject)

# Указываем стандарт C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)



# Добавляем исполняемый файл, указывая исходники из src/ директории
add_executable(sudoku src/main.cpp src/Array2D.h src/Sudoku.cpp src/Sudoku.h src/Matrix.h src/Matrix.cpp src/Game.h src/Game.cpp)
