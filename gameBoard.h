// gameboard.h
#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include <QGridLayout>
#include <QVector>
#include <QMessageBox>

#include "./cellButton.h"

class GameBoard : public QWidget {
    Q_OBJECT
public:
    GameBoard(int rows, int cols, int minesCount, QWidget *parent = nullptr);

    void restartGame();

private slots:
    void handleCellClick(int row, int col);

private:
    GameBoard(QWidget *parent = nullptr);
    
    int rows;
    int cols;  
    int minesCount;

    QGridLayout *gridLayout;
    QVector<QVector<CellButton*>> cells;
    
    int countAdjacentMines(int row, int col) const;

    void setupBoard();
    void placeMines();
    void calculateHints();
    void openCell(int row, int col);
    void revealMines();
    void checkGameStatus();
    void showWinPopup();
    void showLosePopup();
};

#endif // GAMEBOARD_H
