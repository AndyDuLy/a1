# Clear previous artifacts
rm minesweeper
make clean
sudo ldconfig

# Build exec
echo "Building Minesweeper..."
qmake
make

# Run exec
echo "Running Exec"
./minesweeper
