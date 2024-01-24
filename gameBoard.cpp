// gameboard.cpp
#include "./gameBoard.h"
#include "./cellButton.h"
#include <QRandomGenerator>
#include <QIcon>

GameBoard::GameBoard(int rows, int columns, int minesCount, QWidget *parent)
    : QWidget(parent), rows(rows), cols(columns), minesCount(minesCount) {
    setupBoard();
}

void GameBoard::setupBoard() {
    gridLayout->setSpacing(0);
    for (int row = 0; row < 16; ++row) {
        QVector<CellButton*> rowButtons;
        for (int col = 0; col < 30; ++col) {
            CellButton *button = new CellButton(row, col, this);
            gridLayout->addWidget(button, row, col);
            rowButtons.push_back(button);
            connect(button, &CellButton::cellClicked, this, &GameBoard::handleCellClick);
        }
        cells.push_back(rowButtons);
    }
    placeMines();
    calculateHints();
}

void GameBoard::placeMines() {
    QRandomGenerator rand;
    int minesToPlace = minesCount;
    while (minesToPlace > 0) {
        int row = rand.bounded(16);
        int col = rand.bounded(30);
        if (!cells[row][col]->isMine()) {
            cells[row][col]->setMine(true);
            --minesToPlace;
        }
    }
}

void GameBoard::calculateHints() {
    for (int row = 0; row < 16; ++row) {
        for (int col = 0; col < 30; ++col) {
            if (!cells[row][col]->isMine()) {
                int mineCount = 0;
                for (int i = -1; i <= 1; ++i) {
                    for (int j = -1; j <= 1; ++j) {
                        int newRow = row + i;
                        int newCol = col + j;
                        if (newRow >= 0 && newRow < 16 && newCol >= 0 && newCol < 30 &&
                            cells[newRow][newCol]->isMine()) {
                            ++mineCount;
                        }
                    }
                }
                cells[row][col]->setMineCount(mineCount);
            }
        }
    }
}

void GameBoard::handleCellClick(int row, int col) {
    CellButton *button = cells[row][col];

    if (button->isMine()) {
        revealMines();
        showLosePopup();
    } else {
        openCell(row, col);
        checkGameStatus();
    }
}

void GameBoard::openCell(int row, int col) {
    CellButton *button = cells[row][col];

    if (!button->isHidden()) return; // Cell is already open

    button->reveal();

    if (button->mineCount() == 0) {
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                int newRow = row + i;
                int newCol = col + j;
                if (newRow >= 0 && newRow < 16 && newCol >= 0 && newCol < 30) {
                    openCell(newRow, newCol);
                }
            }
        }
    }
}

void GameBoard::revealMines() {
    for (int row = 0; row < 16; ++row) {
        for (int col = 0; col < 30; ++col) {
            if (cells[row][col]->isMine()) {
                cells[row][col]->reveal();
            }
        }
    }
}

void GameBoard::checkGameStatus() {
    int openedCells = 0;
    for (int row = 0; row < 16; ++row) {
        for (int col = 0; col < 30; ++col) {
            if (!cells[row][col]->isMine() && !cells[row][col]->isHidden()) {
                ++openedCells;
            }
        }
    }

    if (openedCells == 16 * 30 - minesCount) {
        showWinPopup();
    }
}

void GameBoard::showWinPopup() {
    QMessageBox::information(this, "Congratulations!", "You won!\nDo you want to play again?");
    restartGame();
}

void GameBoard::showLosePopup() {
    QMessageBox::critical(this, "Game Over", "You hit a mine!\nDo you want to play again?");
    restartGame();
}

void GameBoard::restartGame() {
    for (int row = 0; row < 16; ++row) {
        for (int col = 0; col < 30; ++col) {
            cells[row][col]->reset();
        }
    }
}
