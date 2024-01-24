#!/bin/bash

# Minesweeper Build and Run Script

# Build the Project
echo "Building Minesweeper..."
qmake Minesweeper.pro
make

# Check if the build was successful
if [ $? -ne 0 ]; then
  echo "Build failed. Exiting."
  exit 1
fi

# Run the Game
echo "Running Minesweeper..."
./Minesweeper
