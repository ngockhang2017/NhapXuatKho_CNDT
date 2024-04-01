#ifndef SL_XUATKHO_H
#define SL_XUATKHO_H

#include <QMainWindow>

namespace Ui {
class SL_XuatKho;
}

class SL_XuatKho : public QMainWindow
{
    Q_OBJECT

public:
    explicit SL_XuatKho(QWidget *parent = nullptr);
    ~SL_XuatKho();

    int soluong_hienco;

private slots:
    void on_pushButton_clicked();

private:
    Ui::SL_XuatKho *ui;
};

#endif // SL_XUATKHO_H
