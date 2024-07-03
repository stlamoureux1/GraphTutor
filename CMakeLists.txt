cmake_minimum_required(VERSION 3.5.0)
# build is set up for OSX with brew install of wxWidgets
set(OSX_ARCHITECTURES x86_64)
set(wxWidgets_ROOT_DIR /usr/local/Cellar/wxwidgets)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(GraphTutor)

find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

add_executable(GraphTutor src/GUI/Main.cpp)

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

add_subdirectory(src)
add_subdirectory(test)