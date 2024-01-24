// gameboard.h
#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include <QGridLayout>
#include <QVector>
#include "cellbutton.h"

class GameBoard : public QWidget {
    Q_OBJECT
public:
    GameBoard(QWidget *parent = nullptr);
    void restartGame();

private slots:
    void handleCellClick(int row, int col);

private:
    void setupBoard();
    void placeMines();
    void calculateHints();
    void openCell(int row, int col);
    void revealMines();
    void checkGameStatus();
    void showWinPopup();
    void showLosePopup();

    QGridLayout *gridLayout;
    QVector<QVector<CellButton*>> cells;
    int minesCount;
};

#endif // GAMEBOARD_H
