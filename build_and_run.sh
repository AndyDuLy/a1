# Clear previous artifacts
rm minesweeper
make clean
sudo ldconfig

# Build exec
echo "Building Minesweeper..."
qmake
make

# Run with debug
# g++ -g -fPIC -o minesweeper main.cpp gameBoard.cpp cellButton.cpp qrc_images.cpp moc_gameBoard.cpp moc_cellButton.cpp -I. -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore -L/usr/lib/x86_64-linux-gnu -lQt5Widgets -lQt5Gui -lQt5Core -lGL -lpthread

# Run exec
echo "Running Exec"
./minesweeper
