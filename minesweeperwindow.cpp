// minesweeperwindow.cpp

#include "minesweeperwindow.h"
#include <QGridLayout>
#include <QMessageBox>
#include <QTime>
#include <QVector>
#include <QVariant>
#include <QDebug>


MinesweeperButton::MinesweeperButton(int row, int col, MinesweeperWindow *parent)
    : QPushButton(parent), m_row(row), m_col(col), m_hasMine(false) {
    connect(this, &QPushButton::clicked, parent, &MinesweeperWindow::handleButtonClick);
}

bool MinesweeperButton::hasMine() const {
    return m_hasMine;
}

void MinesweeperButton::setHasMine(bool value) {
    m_hasMine = value;
}

MinesweeperWindow::MinesweeperWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Minesweeper");
    resize(400, 400);

    const int numRows = 30;
    const int numCols = 16;

    QGridLayout *gridLayout = new QGridLayout;
    MinesweeperButton *minesweeperButtons[numRows][numCols];

    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            minesweeperButtons[i][j] = new MinesweeperButton(i, j, this);
            gridLayout->addWidget(minesweeperButtons[i][j], i, j);

            connect(minesweeperButtons[i][j], SIGNAL(clicked(int, int)), this, SLOT(revealEmptySpaces(int, int)));
        }
    }

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(gridLayout);
    setCentralWidget(centralWidget);
}

void MinesweeperWindow::setupGame() {
    mapper = new QSignalMapper(this);
    connect(mapper, SIGNAL(mapped(int)), this, SLOT(revealEmptySpaces(int)));

    buttons = new MinesweeperButton **[16];
    revealedCells = new bool *[16];
    mines = new bool *[16];

    for (int i = 0; i < 16; ++i) {
        buttons[i] = new MinesweeperButton *[30];
        revealedCells[i] = new bool[30];
        mines[i] = new bool[30];

        for (int j = 0; j < 30; ++j) {
            buttons[i][j] = new MinesweeperButton(i, j, this);
            buttons[i][j]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            buttons[i][j]->setFixedSize(30, 30);
            mapper->setMapping(buttons[i][j], i * 30 + j);
            connect(buttons[i][j], SIGNAL(clicked()), mapper, SLOT(map()));

            revealedCells[i][j] = false;
            mines[i][j] = false;
        }
    }

    placeMines();
}

void MinesweeperWindow::placeMines() {
    int minesToPlace = 99;

    while (minesToPlace > 0) {
        int row = rand() % 16;
        int col = rand() % 30;
        MinesweeperButton *button = buttons[row][col];
        if (!button->hasMine()) {
            button->setHasMine(true);
            mines[row][col] = true;
            --minesToPlace;
        }
    }
}

void MinesweeperWindow::handleButtonClick() {
    MinesweeperButton* button = qobject_cast<MinesweeperButton*>(sender());
    if (button) {
        revealEmptySpaces(button->property("row").toInt(), button->property("col").toInt());
    }
}

bool MinesweeperWindow::isCellRevealed(int row, int col) const {
    return revealedCells[row][col];
}

bool MinesweeperWindow::isMine(int row, int col) const {
    return mines[row][col];
}

void MinesweeperWindow::setCellRevealed(int row, int col, bool revealed) {
    revealedCells[row][col] = revealed;
}

void MinesweeperWindow::revealEmptySpaces(int row, int col) {
    if (isCellRevealed(row, col) || isMine(row, col)) {
        return;
    }

    setCellRevealed(row, col, true);
    qDebug() << "Revealing empty space at row:" << row << ", col:" << col;

    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int newRow = row + i;
            int newCol = col + j;

            if (isValidCell(newRow, newCol)) {
                revealEmptySpaces(newRow, newCol);
            }
        }
    }
}

bool MinesweeperWindow::isValidCell(int row, int col) const {
    return row >= 0 && row < 16 && col >= 0 && col < 30;
}

void MinesweeperWindow::gameOver(bool win) {
    QString message = win ? "You win!" : "Game over!";
    QMessageBox::information(this, "Game Over", message);
    setupGame();
}
