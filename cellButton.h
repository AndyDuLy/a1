// cellbutton.h
#ifndef CELLBUTTON_H
#define CELLBUTTON_H

#include <QPushButton>

class CellButton : public QPushButton {
    Q_OBJECT
public:
    CellButton(int row, int col, QWidget *parent = nullptr);
    int getRow() const;
    int getCol() const;
    bool isMine() const;
    int mineCount() const;
    bool isHidden() const;

public slots:
    void reveal();

signals:
    void cellClicked(int row, int col, Qt::MouseButtons buttons);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    void handleRightClick();

    int row;
    int col;
    bool mine;
    int mineCount;
    bool flagged;
    bool questioned;
};

#endif // CELLBUTTON_H
