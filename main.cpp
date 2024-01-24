// main.cpp
#include <QApplication>
#include "./gameBoard.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    GameBoard game(16, 30, 99);
    game.show();
    return a.exec();
}
