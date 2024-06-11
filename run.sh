#!/bin/bash

# Get the directory where this script is located
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

# Navigate to the script directory
cd "$SCRIPT_DIR"

# Initialize variables
BUILD_TYPE="Debug"
TIMED_RUN=false
DELETE_BUILD=false
GPU=false

# Parse arguments
for arg in "$@"; do
    case "${arg,,}" in
        ("r")
            BUILD_TYPE="Release"
            ;;
        ("t")
            TIMED_RUN=true
            ;;
        ("b")
            DELETE_BUILD=true
            ;;
        ("g")
            GPU=true
            ;;
    esac
done

echo -e "\033[34mBuilding in $BUILD_TYPE mode...\033[0m"

# Remove existing build directory if it exists
rm -rf build

# Generate Makefiles and build the project with the specified build type
cmake -DCMAKE_BUILD_TYPE="$BUILD_TYPE" -S . -B build/

EXIT_STATUS=$?

# Check if build was successful
if [ $EXIT_STATUS -ne 0 ]; then
    echo -e "\033[31mCMake failed.\033[0m"
    exit $EXIT_STATUS
fi

# Check if the configuration file exists
CONFIG_FILE="build/project_config.sh"
if [ ! -f "$CONFIG_FILE" ]; then
    echo -e "\033[34mConfiguration file not found: $CONFIG_FILE\033[0m"
    exit 1
fi

# Build the project
cmake --build build/

EXIT_STATUS=$?

# Check if build was successful
if [ $EXIT_STATUS -ne 0 ]; then
    echo -e "\033[31mBuild failed.\033[0m"
    exit $EXIT_STATUS
fi

# Source the project name
source "$CONFIG_FILE"

# Determine the executable path
if [ "$GPU" = true ]; then
    echo -e "\033[34mRunning with GPU support...\033[0m"
    EXECUTABLE="__NV_PRIME_RENDER_OFFLOAD=1 __GLX_VENDOR_LIBRARY_NAME=nvidia ./build/$BUILD_TYPE/$PROJECT_NAME"
else
    EXECUTABLE="./build/$BUILD_TYPE/$PROJECT_NAME"
fi

# Run the executable with the remaining arguments
if [ "$TIMED_RUN" = true ]; then
    eval "time $EXECUTABLE"
else
    eval "$EXECUTABLE"
fi

# Print the exit status
EXIT_STATUS=$?
if [ $EXIT_STATUS -eq 0 ]; then
    echo -e "\033[32mProgram exited successfully.\033[0m"
else
    echo -e "\033[31mProgram exited with status $EXIT_STATUS.\033[0m"
fi

# Check if the build directory should be deleted
if [ "$DELETE_BUILD" = true ]; then
    rm -rf build
    echo -e "\033[34mBuild directory deleted.\033[0m"
fi
