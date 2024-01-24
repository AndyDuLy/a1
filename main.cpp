// main.cpp
#include <QApplication>
#include "./gameBoard.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    GameBoard game;
    game.show();
    return a.exec();
}
