#project and settings
CMAKE_MINIMUM_REQUIRED(VERSION 3.22)
set (CMAKE_CXX_STANDARD 17)

project(skia)

#find opengl
find_package(OpenGL REQUIRED)

if (OPENGL_FOUND)
    message("opengl found")
else (OPENGL_FOUND)
    message("opengl not found")
endif()

#freetype and fontconfig
find_package(Freetype REQUIRED)
if (FREETYPE_FOUND)
    message("freetype found")
else (FREETYPE_FOUND)
    message("freetype not found")
endif()

find_package(Fontconfig REQUIRED)
if (FONTCONFIG_FOUND)
    message("fontconfig found")
else (FONTCONFIG_FOUND)
    message("fontconfig not found")
endif()

#build glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_SOURCE_DIR}/glfw)

#source files
#FILE(GLOB SOURCE_FILES src/cpp/**/*.cpp)
#add target
add_executable(skiatest main.cpp ${SOURCE_FILES})

#include dirs
target_include_directories(skiatest PRIVATE ${OPENGL_INCLUDE_DIRS})
target_include_directories(skiatest PRIVATE ${FREETYPE_INCLUDE_DIRS})
target_include_directories(skiatest PRIVATE ${Fontconfig_INCLUDE_DIRS})
target_include_directories(skiatest PRIVATE glfw/include)
target_include_directories(skiatest PRIVATE glfw/deps)
target_include_directories(skiatest PRIVATE .)

#libraries
target_link_directories(skiatest PRIVATE ${CMAKE_SOURCE_DIR}/lib)

#link libraries
target_link_libraries(skiatest ${OPENGL_LIBRARIES} ${FREETYPE_LIBRARIES} ${Fontconfig_LIBRARIES} skia glfw)
# target_link_libraries(skiatest ${OPENGL_LIBRARIES} skia glfw)