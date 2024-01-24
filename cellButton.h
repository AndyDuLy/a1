// cellButton.h
#ifndef CELLBUTTON_H
#define CELLBUTTON_H

#include <QPushButton>

class CellButton : public QPushButton {
    Q_OBJECT
public:
    CellButton(int row, int col, QWidget *parent = nullptr);

    bool isMine() const;
    bool isHidden() const;
    int mineCount() const;

    void setMine(bool value);
    void setMineCount(int count);
    void reveal();
    void reset();

signals:
    void cellClicked(int row, int col);

private slots:
    void handleLeftClick();
    void handleRightClick();

private:
    int row;
    int col;
    bool mine;
    int mineCountValue;
    bool hidden;
};

#endif // CELLBUTTON_H
