#ifndef MINESWEEPERWINDOW_H
#define MINESWEEPERWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QSignalMapper>

class MinesweeperWindow;

class MinesweeperButton : public QPushButton {
    Q_OBJECT

public:
    MinesweeperButton(int row, int col, MinesweeperWindow *parent);
    bool hasMine() const;
    void setHasMine(bool value);

signals:
    void clicked(int row, int col);

private:
    int m_row;
    int m_col;
    bool m_hasMine;
};

class MinesweeperWindow : public QMainWindow {
    Q_OBJECT

public:
    MinesweeperWindow(QWidget *parent = nullptr);

public slots:
    void revealEmptySpaces(int row, int col);
    void handleButtonClick();
    
private:
    void setupGame();
    void placeMines();
    int countMines(int row, int col);
    void gameOver(bool win);
    bool checkWin();
    
    bool isCellRevealed(int row, int col) const;
    bool isMine(int row, int col) const;
    void setCellRevealed(int row, int col, bool revealed);
    bool isValidCell(int row, int col) const;

    int minesCount;
    MinesweeperButton ***buttons;
    QSignalMapper *mapper;
    bool **revealedCells;
    bool **mines; 
};

#endif
