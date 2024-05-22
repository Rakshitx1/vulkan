#!/bin/bash

# Get the directory where this script is located
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

# Save the current directory
CURRENT_DIR=$(pwd)

# Navigate to the script directory
cd "$SCRIPT_DIR"

# Determine build type based on input argument
if [[ "${1,,}" == "release" || "${1,,}" == "r" ]]; then
    BUILD_TYPE="Release"
    echo -e "\e[1;34mBuilding in Release mode...\e[0m"
else
    BUILD_TYPE="Debug"
    echo -e "\e[1;34mBuilding in Debug mode...\e[0m"
fi

# Remove existing build directory if it exists
if [ -d "build" ]; then
    echo -e "\e[1;33mRemoving existing build directory...\e[0m"
    rm -rf build
fi

# Create a new build directory
mkdir -p build
cd build

# Generate Makefiles and build the project with the specified build type
cmake -DCMAKE_BUILD_TYPE="$BUILD_TYPE" ..

# Build the project
make

# Run the executable
./$BUILD_TYPE/VulkanTest

# Return to the initial directory
cd "$CURRENT_DIR"