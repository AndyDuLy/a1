#include <QApplication>
#include "minesweeperwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MinesweeperWindow window;
    window.show();

    return a.exec();
}
