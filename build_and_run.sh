#!/bin/bash

# Minesweeper Build and Run Script

# Clear old files if exists and reset
rm minesweeper
make clean
sudo ldconfig

# Build the Project
echo "Building Minesweeper..."
qmake minesweeper.pro
make

# Check if the build was successful
if [ $? -ne 0 ]; then
  echo "Build failed. Exiting."
  exit 1
fi

# Run the Game
echo "Running Minesweeper..."
./minesweeper
