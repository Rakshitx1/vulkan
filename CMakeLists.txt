cmake_minimum_required(VERSION 3.10)

project(VulkanTest VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the build type to Debug by default if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release)

# Find Vulkan
find_package(Vulkan REQUIRED)

# Find GLFW3
find_package(glfw3 3.3 REQUIRED)

# List your source files
set(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
)

# Create an executable
add_executable(VulkanTest ${SOURCES})

# Set compiler flags for Debug
target_compile_options(VulkanTest PRIVATE $<$<CONFIG:DEBUG>: -O0 -g -Wall> )

# Set compiler flags for Release
target_compile_options(VulkanTest PRIVATE $<$<CONFIG:RELEASE>: -O2>)

# Link the executable with Vulkan and GLFW libraries
target_link_libraries(VulkanTest PRIVATE ${Vulkan_LIBRARIES} glfw)

# Link against additional required libraries
if(UNIX)
    target_link_libraries(VulkanTest PRIVATE dl pthread X11 Xxf86vm Xrandr Xi)
endif()
