// cellbutton.cpp
#include "./cellButton.h"
#include <QMouseEvent>

CellButton::CellButton(int row, int col, QWidget *parent)
    : QPushButton(parent), row(row), col(col), mine(false), mineCount(0) {
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void CellButton::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        handleRightClick();
    } else {
        QPushButton::mousePressEvent(event);
    }
}

void CellButton::handleRightClick() {
    if (isHidden()) {
        if (flagged) {
            setIcon(QIcon(":/minesweeper_icons/question_mark.jpg"));
            flagged = false;
        } else if (questioned) {
            setIcon(QIcon());
            questioned = false;
        } else {
            setIcon(QIcon(":/minesweeper_icons/mine_flag.png"));
            flagged = true;
        }
    }
}

void CellButton::reveal() {
    setEnabled(false);
    setStyleSheet("background-color: lightgray;");
    if (mine) {
        setIcon(QIcon(":/minesweeper_icons/bomb.png"));
    } else {
        if (mineCount > 0) {
            setText(QString::number(mineCount));
        }
    }
}
