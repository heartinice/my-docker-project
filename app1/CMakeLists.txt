cmake_minimum_required(VERSION 3.10)
project(app1)

# Указываем стандарт C++
set(CMAKE_CXX_STANDARD 17)

# Указываем библиотеку SQLite3
find_package(SQLite3 REQUIRED)

# Добавляем исполняемый файл
add_executable(app1 main.cpp)
target_link_libraries(app1 SQLite::SQLite3)

