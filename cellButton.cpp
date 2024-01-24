// cellButton.cpp
#include "./cellButton.h"
#include <QIcon>

CellButton::CellButton(int row, int col, QWidget *parent)
    : QPushButton(parent), row(row), col(col), mine(false), mineCountValue(0), hidden(true) {
    setFixedSize(25, 25);
    connect(this, &QPushButton::clicked, this, &CellButton::handleLeftClick);
    connect(this, &QPushButton::customContextMenuRequested, this, &CellButton::handleRightClick);
}

bool CellButton::isMine() const {
    return mine;
}

bool CellButton::isHidden() const {
    return hidden;
}

int CellButton::mineCount() const {
    return mineCountValue;
}

void CellButton::setMine(bool value) {
    mine = value;
}

void CellButton::setMineCount(int count) {
    mineCountValue = count;
}

void CellButton::reveal() {
    if (mine) {
        setStyleSheet("background-color: red");
        setIcon(QIcon(":/minesweeper_icons/bomb.png"));
    } else {
        setStyleSheet("background-color: lightgray");
        if (mineCountValue > 0) {
            setText(QString::number(mineCountValue));
        }
    }
    hidden = false;
}

void CellButton::handleLeftClick() {
    if (!mine) {
        emit cellClicked(row, col);
    }
}

void CellButton::handleRightClick() {
    if (hidden) {
        if (text() == "") {
            setText("?");
            setIcon(QIcon(":/minesweeper_icons/question_mark.jpg"));
        } else if (text() == "?") {
            setText("");
            setIcon(QIcon());
        }
    }
}

void CellButton::reset() {
    mine = false;
    mineCountValue = 0;
    hidden = true;
    setText("");
    setIcon(QIcon());
    setStyleSheet("");
}
