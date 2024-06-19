#ifndef QUANLY_TK_H
#define QUANLY_TK_H

#include <QMainWindow>

namespace Ui {
class QuanLy_TK;
}

class QuanLy_TK : public QMainWindow
{
    Q_OBJECT

public:
    explicit QuanLy_TK(QWidget *parent = nullptr);
    ~QuanLy_TK();

private:
    Ui::QuanLy_TK *ui;
};

#endif // QUANLY_TK_H
